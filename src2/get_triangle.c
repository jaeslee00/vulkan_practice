/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 02:38:05 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/17 19:10:03 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	get_vtx_info(t_vertex *vertex, float vtx1, float vtx2, float vtx3,
						float r, float g, float b)
{
	vertex->pos[0] = vtx1;
	vertex->pos[1] = vtx2;
	vertex->pos[2] = vtx3;
	vertex->color[0] = r;
	vertex->color[1] = g;
	vertex->color[2] = b;
}

void	get_triangle_info(t_vulkan *vulkan)
{
	t_vertex	tri_vtx;

	array_init(&vulkan->triangle, sizeof(t_vertex));

	get_vtx_info(&tri_vtx, -0.5f, -0.5f, -0.1f, 0.0f, 1.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.5f, -0.5f, -0.1f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.5f, 0.5f, -0.1f, 0.0f, 0.0f, 1.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -0.5f, 0.5f, -0.1f, 1.0f, 0.0f, 1.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);

	get_vtx_info(&tri_vtx, -0.5f, -0.5f, -0.3f, 1.0f, 1.0f, 1.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.5f, -0.5f, -0.3f, 1.0f, 1.0f, 1.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.5f, 0.5f, -0.3f, 1.0f, 1.0f, 1.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -0.5f, 0.5f, -0.3f, 1.0f, 1.0f, 1.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);

	vulkan->vertices_index = (uint32_t*)malloc(12 * sizeof(uint32_t));
	vulkan->vertices_index[0] = 0;
	vulkan->vertices_index[1] = 1;
	vulkan->vertices_index[2] = 2;
	vulkan->vertices_index[3] = 2;
	vulkan->vertices_index[4] = 3;
	vulkan->vertices_index[5] = 0;

	vulkan->vertices_index[6] = 4;
	vulkan->vertices_index[7] = 5;
	vulkan->vertices_index[8] = 6;
	vulkan->vertices_index[9] = 6;
	vulkan->vertices_index[10] = 7;
	vulkan->vertices_index[11] = 4;
}
