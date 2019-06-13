/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 02:38:05 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/13 18:30:34 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "vector.h"

uint32_t	add_vertex(t_vulkan *vk, float *position, float r, float g, float b)
{
	t_vertex_info	vtx_info = {};

	vtx_info.pos[0] = position[0];
	vtx_info.pos[1] = position[1];
	vtx_info.pos[2] = position[2];
	vec3_normalize(vtx_info.pos);
	vtx_info.color[0] = r;
	vtx_info.color[1] = g;
	vtx_info.color[2] = b;
	array_push_back(&vk->vtx, &vtx_info);
	return (vk->vtx.length - 1);
}

void	add_color(float *pos, float *color)
{
	float	size;

	size = vec3_size(pos);
	if (size < 1.005f)
	{
		color[0] = 130.f / 255.f * size * size * size;
		color[1] = 200.f / 255.f * size * size * size;
		color[2] = 230.f / 255.f * size * size * size;
	}
	else if (size < 1.02f)
	{
		color[0] = 255.f / 255.f * size;
		color[1] = 222.f / 255.f * size;
		color[2] = 173.f / 255.f * size;
	}
	else if (size < 1.17f)
	{
		color[0] *= 1.3f/(size * size * size * size);
		color[1] *= 1.3f/(size * size * size * size);
		color[2] *= 1.3f/(size * size * size * size);
	}
	if (size > 1.17f)
	{
		color[0] = 1.0f;
		color[1] = 1.f;
		color[2] = 1.f;
	}
}
