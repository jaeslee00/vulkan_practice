/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:19:32 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/28 10:55:36 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "open-simplex-noise.h"

void	create_landscape(t_vulkan *vk)
{
	struct osn_context	*ctx;
	size_t				vtx_index;
	t_vertex_info		*vtx;
	t_noise_attr		attr;
	float				elevation;
	/* min and max elevation */
	size_t				min_i;
	size_t				max_i;
	float				min = 10.f;
	float				max = 0.0f;

	attr.amplitude = 1.0f;
	attr.freq = 1.0f;
	attr.freq_delta = 2.28f;
	attr.amp_delta = 0.47f;
	attr.layers = 10;

	open_simplex_noise(1274, &ctx); // seed : 1274
	vtx_index = 0;
	vtx = (t_vertex_info*)vk->vtx.ptr;
	printf("nbr of triangles : %zu\n", vk->tri_faces.length);
	printf("nbr of vtx : %zu\n", vk->vtx.length);
	while (vtx_index < vk->vtx.length)
	{
		elevation = noise_filter(ctx, vtx[vtx_index].pos, &attr);
		vec3_scale(vtx[vtx_index].pos, elevation);
		add_color(vtx[vtx_index].pos, vtx[vtx_index].color);
		//ft_bzero(vtx[vtx_index].color, sizeof(float) * 3);
		vtx_index++;
		// if (vec3_size(pos) < min)
		// {
		// 	min = vec3_size(pos);
		// 	min_i = i;
		// }
		// if (vec3_size(pos) > max)
		// {
		// 	max = vec3_size(pos);
		// 	max_i = i;
		// }
	}
	//printf("min_pos[%zu] : %f\nmax_pos[%zu] : %f\n", min_i, min, max_i, max);
}

void	get_normals(t_array *tri_normals, t_array *tri_faces, t_array *vtx)
{
	//삼각형 ABC
	//삼각형 노말 vec3_cross(B-A, B-C)
	uint32_t	vtx1;
	uint32_t	vtx2;
	uint32_t	vtx3;
	uint32_t	tri_index;
	float		normal[3];
	float		ba[3];
	float		bc[3];

	tri_index = 0;
	while (tri_index < tri_faces->length)
	{
		vtx1 = ((t_tri_vtx_indices*)tri_faces->ptr)[tri_index].v1;
		vtx2 = ((t_tri_vtx_indices*)tri_faces->ptr)[tri_index].v2;
		vtx3 = ((t_tri_vtx_indices*)tri_faces->ptr)[tri_index].v3;
		vec3_sub(ba, ((t_vertex_info*)vtx->ptr)[vtx2].pos, ((t_vertex_info*)vtx->ptr)[vtx1].pos);
		vec3_sub(bc, ((t_vertex_info*)vtx->ptr)[vtx2].pos, ((t_vertex_info*)vtx->ptr)[vtx3].pos);
		vec3_cross(normal, ba, bc);
		array_push_back(tri_normals, normal);
		tri_index++;
	}
}

void	create_cube_surface(t_vulkan *vk, int resolution, float *up_vec, int normalize)
{
	float	vec_vert[3];
	float	vec_horiz[3];
	float	tmp_v;
	float	tmp_h;
	float	position[3];
	size_t	vtx_index;

	vec_horiz[0] = up_vec[1];
	vec_horiz[1] = up_vec[2];
	vec_horiz[2] = up_vec[0];
	vec3_cross(vec_vert, up_vec, vec_horiz);
	for (int i=0; i < resolution; i++)
	{
		for (int j=0; j < resolution; j++)
		{
			tmp_h = (((float)i / ((float)(resolution - 1))) - 0.5f) * 2.f;
			tmp_v = (((float)j / ((float)(resolution - 1))) - 0.5f) * 2.f;
			position[0] = up_vec[0] + tmp_h * vec_horiz[0] + tmp_v * vec_vert[0];
			position[1] = up_vec[1] + tmp_h * vec_horiz[1] + tmp_v * vec_vert[1];
			position[2] = up_vec[2] + tmp_h * vec_horiz[2] + tmp_v * vec_vert[2];
			if (normalize)
				vec3_normalize(position);
			vtx_index = add_vertex(vk, position, 0.0f, 0.5f, 0.0f);
			if (i < resolution - 1 && j < resolution - 1)
			{
				array_push_back(&vk->tri_faces,
					&(t_tri_vtx_indices[]){vtx_index, vtx_index + resolution, vtx_index + resolution + 1});
				array_push_back(&vk->tri_faces,
					&(t_tri_vtx_indices[]){vtx_index, vtx_index + resolution + 1, vtx_index + 1});
			}
		}
	}
}

void	create_cube(t_vulkan *vk, int resolution)
{

	array_init(&vk->vtx, sizeof(t_vertex_info));
	array_init(&vk->tri_faces, sizeof(t_tri_vtx_indices));
	array_init(&vk->tri_normals, sizeof(float) * 3);
	create_cube_surface(vk, resolution, (float[]){0.0, 0.0, 1.0f}, 1);
	create_cube_surface(vk, resolution, (float[]){0.0, 0.0, -1.0f}, 1);
	create_cube_surface(vk, resolution, (float[]){0.0, 1.0, 0.0f}, 1);
	create_cube_surface(vk, resolution, (float[]){0.0, -1.0, 0.0f}, 1);
	create_cube_surface(vk, resolution, (float[]){1.0, 0.0, 0.0f}, 1);
	create_cube_surface(vk, resolution, (float[]){-1.0, 0.0, 0.0f}, 1);
	get_normals(&vk->tri_normals, &vk->tri_faces, &vk->vtx);
	create_landscape(vk);
}
// 2 3 5 9 17
