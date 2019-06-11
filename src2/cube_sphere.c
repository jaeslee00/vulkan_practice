/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:19:32 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/11 17:16:13 by jaelee           ###   ########.fr       */
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
			// if (up_vec[0] == 1.0)
			// 	vtx_index = add_vertex(vk, position, 1.0f, 0.0f, 0.0f); //RED
			// if (up_vec[0] == -1.0)
			// 	vtx_index = add_vertex(vk, position, 0.0f, 1.0f, 0.0f); //GREEN
			// if (up_vec[1] == 1.0)
			// 	vtx_index = add_vertex(vk, position, 0.0f, 0.0f, 1.0f); //BLUE
			// if (up_vec[1] == -1.0)
			// 	vtx_index = add_vertex(vk, position, 0.0f, 1.0f, 1.0f); //CYAN
			// if (up_vec[2] == 1.0)
			// 	vtx_index = add_vertex(vk, position, 1.0f, 1.0f, 1.0f); //WHITE
			// if (up_vec[2] == -1.0)
			// 	vtx_index = add_vertex(vk, position, 1.0f, 1.0f, 0.0f); //YELLOW
			vtx_index = add_vertex(vk, position, 0.0f, 0.6f, 0.0f);
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
	struct osn_context	*ctx2;
	size_t				i;
	float				*pos;
	float				*color;
	double				value;
	double				value2;
		float	min  = 10.0f;
		float	max = 0.0f;
	array_init(&vk->vtx, sizeof(t_vertex_info));
	array_init(&vk->tri_faces, sizeof(t_tri_vtx_indices));
	create_cube_surface(vk, resolution, (float[]){0.0, 0.0, 1.0f});
	create_cube_surface(vk, resolution, (float[]){0.0, 0.0, -1.0f});
	create_cube_surface(vk, resolution, (float[]){0.0, 1.0, 0.0f});
	create_cube_surface(vk, resolution, (float[]){0.0, -1.0, 0.0f});
	create_cube_surface(vk, resolution, (float[]){1.0, 0.0, 0.0f});
	create_cube_surface(vk, resolution, (float[]){-1.0, 0.0, 0.0f});
	open_simplex_noise(1379471, &ctx);
	open_simplex_noise(1379471, &ctx2);
	i = 0;
	while (i < vk->vtx.length)
	{
		pos = ((t_vertex_info*)vk->vtx.ptr)[i].pos;
		color = ((t_vertex_info*)vk->vtx.ptr)[i].color;
		float	*freq_pos;
		float	*freq_pos2;
		memcpy(freq_pos, pos, sizeof(float[3]));
		memcpy(freq_pos2, pos, sizeof(float[3]));
		vec3_scale(freq_pos, 8.5f);
		vec3_scale(freq_pos2, 5.f);
		value = open_simplex_noise3(ctx, freq_pos[0], freq_pos[1], freq_pos[2]);
		value = 1.f + value * 0.5f;
		value2 = open_simplex_noise3(ctx2, freq_pos2[0], freq_pos2[1], freq_pos2[2]);
		value2 = 1.f - value * 0.5f;
		value = value + value2;
		vec3_scale(pos, (float)value);
		// if (vec3_size(pos) < min)
		// {
		// 	min = vec3_size(pos);
		// }
		// if (vec3_size(pos) > max)
		// {
		// 	max = vec3_size(pos);
		// }
		if (vec3_size(pos) < 1.545f)
		{
			color[0] = 0.0f;
			color[1] = 0.0f;
			color[2] = 1.0f;
		}
		else if (vec3_size(pos) < 1.56f)
		{
			color[0] = 255.f / 255.f;
			color[1] = 222.f / 255.f;
			color[2] = 173.f / 255.f;
		}
		else if (vec3_size(pos) > 1.67f)
		{
			color[0] = 1.0f;
			color[1] = 1.f;
			color[2] = 1.f;
		}
		//vec3_scale(pos, (float)value2);
		i++;
	}
}
	// add_vertex(vk, (float[]){-0.5f, 0.5f, 0.5f}, 0.0f, 0.0f, 0.0f);
	// add_vertex(vk, (float[]){0.5f, 0.5f, 0.5f}, 0.0f, 0.0f, 0.0f);
	// add_vertex(vk, (float[]){0.5f, -0.5f, 0.5f}, 0.0f, 0.0f, 0.0f);
	// add_vertex(vk, (float[]){-0.5f, -0.5f, 0.5f}, 0.0f, 0.0f, 0.0f);

	// add_vertex(vk, (float[]){-0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 0.0f);
	// add_vertex(vk, (float[]){0.5f, 0.5f, -0.5f}, 0.0f, 0.0f, 0.0f);
	// add_vertex(vk, (float[]){0.5f, -0.5f, -0.5f}, 0.0f, 0.0f, 0.0f);
	// add_vertex(vk, (float[]){-0.5f, -0.5f, -0.5f}, 0.0f, 0.0f, 0.0f);

