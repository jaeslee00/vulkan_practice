/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 02:38:05 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/27 14:15:12 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	get_vtx_info(t_vertex *vertex, float vtx1, float vtx2, float r, float g, float b)
{
	vertex->pos[0] = vtx1;
	vertex->pos[1] = vtx2;

	vertex->color[0] = r;
	vertex->color[1] = g;
	vertex->color[2] = b;
}

void	get_triangle_info(t_vulkan *vulkan)
{
	t_vertex	tri_vtx;

	array_init(&vulkan->triangle, sizeof(t_vertex));
	get_vtx_info(&tri_vtx, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);

	vulkan->vertices_index = (uint32_t*)malloc(6 * sizeof(uint32_t));
	vulkan->vertices_index[0] = 0;
	vulkan->vertices_index[1] = 1;
	vulkan->vertices_index[2] = 2;
	vulkan->vertices_index[3] = 2;
	vulkan->vertices_index[4] = 3;
	vulkan->vertices_index[5] = 0;
}
