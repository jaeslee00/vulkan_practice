/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 02:38:05 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/13 16:38:13 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	get_vtx_info(t_vertex *vertex, float vtx1, float vtx2, float vtx3, float r, float g, float b)
{
	vertex->pos[0] = vtx1;
	vertex->pos[1] = vtx2;
//	vertex->pos[2] = vtx3; /*TODO depth... for cube*/

	vertex->color[0] = r;
	vertex->color[1] = g;
	vertex->color[2] = b;
}

void	get_triangle_info(t_vulkan *vulkan)
{
	t_vertex	tri_vtx;

	array_init(&vulkan->triangle, sizeof(t_vertex));
	get_vtx_info(&tri_vtx, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	/* CUBE
	get_vtx_info(&tri_vtx, 0.0f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 2.0f,  5.0f, -15.0f, 0.0f, 1.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -1.5f, -2.2f, -2.5f, 1.0f, 0.0f, 1.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -3.8f, -2.0f, -12.3f, 1.0f, 0.0f, 1.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 2.4f, -0.4f, -3.5f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -1.7f,  3.0f, -7.5f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 1.3f, -2.0f, -2.5f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 1.5f,  2.0f, -2.5f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 1.5f,  0.2f, -1.5f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -1.3f,  1.0f, -1.5f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vulkan->triangle, &tri_vtx);
	*/
	vulkan->vertices_index = (uint32_t*)malloc(6 * sizeof(uint32_t));
	vulkan->vertices_index[0] = 0;
	vulkan->vertices_index[1] = 1;
	vulkan->vertices_index[2] = 2;
	vulkan->vertices_index[3] = 2;
	vulkan->vertices_index[4] = 3;
	vulkan->vertices_index[5] = 0;
}
