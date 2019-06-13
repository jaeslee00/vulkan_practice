/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:19:32 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/13 23:26:19 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "open-simplex-noise.h"


void	create_cube_surface(t_vulkan *vk, int resolution, float *up_vec)
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
			vtx_index = add_vertex(vk, position, 0.0f, 0.5f, 0.0f);
			if (i < resolution - 1 && j < resolution - 1)
			{
				array_push_back(&vk->tri_faces,
					&(t_tri_vtx_indices){vtx_index, vtx_index + resolution, vtx_index + resolution + 1});
				array_push_back(&vk->tri_faces,
					&(t_tri_vtx_indices){vtx_index, vtx_index + resolution + 1, vtx_index + 1});
			}
		}
	}
}


void	create_cube(t_vulkan *vk, int resolution)
{
	struct osn_context	*ctx;
	size_t				vtx_index;
	double				noise_value = 0.0;
	float				amplitude = 1.0f;
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
	attr.persistence = 0.47f;
	attr.layers = 10;
	array_init(&vk->vtx, sizeof(t_vertex_info));
	array_init(&vk->tri_faces, sizeof(t_tri_vtx_indices));
	create_cube_surface(vk, resolution, (float[]){0.0, 0.0, 1.0f});
	create_cube_surface(vk, resolution, (float[]){0.0, 0.0, -1.0f});
	create_cube_surface(vk, resolution, (float[]){0.0, 1.0, 0.0f});
	create_cube_surface(vk, resolution, (float[]){0.0, -1.0, 0.0f});
	create_cube_surface(vk, resolution, (float[]){1.0, 0.0, 0.0f});
	create_cube_surface(vk, resolution, (float[]){-1.0, 0.0, 0.0f});
	open_simplex_noise(1274, &ctx); // seed : 17971
	vtx_index = 0;
	vtx = (t_vertex_info*)vk->vtx.ptr;
	printf("vertex no = %zu\n", vk->vtx.length);
	while (vtx_index < vk->vtx.length)
	{
		elevation = noise_filter(ctx, vtx[vtx_index].pos, &attr);
		vec3_scale(vtx[vtx_index].pos, elevation);
		add_color(vtx[vtx_index].pos, vtx[vtx_index].color);
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
//	printf("min_pos[%zu] : %f\nmax_pos[%zu] : %f\n", min_i, min, max_i, max);
}
