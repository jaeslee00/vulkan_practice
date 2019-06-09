/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 02:38:05 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/09 19:32:41 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "vector.h"

uint32_t	add_vertex(t_vulkan *vk, float *position, float r, float g, float b)
{
	t_vertex_info	vtx_info;

	vtx_info.pos[0] = position[0];
	vtx_info.pos[1] = position[1];
	vtx_info.pos[2] = position[2];
	vec3_normalize(vtx_info.pos);
	vtx_info.color[0] = r;
	vtx_info.color[1] = g;
	vtx_info.color[2] = b;
	vtx_info.tex_coord[0] = 0.0f;
	vtx_info.tex_coord[1] = 0.0f;
	array_push_back(&vk->vtx, &vtx_info);
	return (vk->vtx.length - 1);
}
