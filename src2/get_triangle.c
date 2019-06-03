/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 02:38:05 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/03 02:13:52 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	get_vtx_info(t_vertex *vertex, float vtx1, float vtx2, float vtx3,
						float r, float g, float b, float tex1, float tex2)
{
	vertex->pos[0] = vtx1;
	vertex->pos[1] = vtx2;
	vertex->pos[2] = vtx3;
	vertex->color[0] = r;
	vertex->color[1] = g;
	vertex->color[2] = b;
	vertex->tex_coord[0] = tex1;
	vertex->tex_coord[1] = tex2;
}

void	get_triangle_info(t_vulkan *vk)
{
	t_vertex	tri_vtx;

	array_init(&vk->triangle, sizeof(t_vertex));

	/* back */
	get_vtx_info(&tri_vtx, -0.3f, -0.3f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.3f, -0.3f, -0.3f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.3f, 0.3f, -0.3f, 0.0f, 0.0f, 1.0f, 2.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -0.3f, 0.3f, -0.3f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);

	/* front */
	get_vtx_info(&tri_vtx, -0.3f, -0.3f, 0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.3f, -0.3f, 0.3f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.3f, 0.3f, 0.3f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -0.3f, 0.3f, 0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);

	/* bottom */
	get_vtx_info(&tri_vtx, -0.3f, -0.3f, 0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -0.3f, -0.3f, -0.3f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.3f, -0.3f, -0.3f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.3f, -0.3f, 0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);

	/* top */
	get_vtx_info(&tri_vtx, 0.3f, 0.3f, -0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.3f, 0.3f, 0.3f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -0.3f, 0.3f, 0.3f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -0.3f, 0.3f, -0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);


	get_vtx_info(&tri_vtx, 0.3f, -0.3f, -0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.3f, -0.3f, 0.3f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.3f, 0.3f, 0.3f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, 0.3f, 0.3f, -0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);


	get_vtx_info(&tri_vtx, -0.3f, 0.3f, 0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -0.3f, 0.3f, -0.3f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -0.3f, -0.3f, -0.3f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -0.3f, -0.3f, 0.3f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);

	vk->vertices_index = (uint32_t*)malloc(36 * sizeof(uint32_t));
	vk->vertices_index[0] = 0;
	vk->vertices_index[1] = 1;
	vk->vertices_index[2] = 2;
	vk->vertices_index[3] = 2;
	vk->vertices_index[4] = 3;
	vk->vertices_index[5] = 0;

	vk->vertices_index[6] = 4;
	vk->vertices_index[7] = 5;
	vk->vertices_index[8] = 6;
	vk->vertices_index[9] = 6;
	vk->vertices_index[10] = 7;
	vk->vertices_index[11] = 4;

	vk->vertices_index[12] = 8;
	vk->vertices_index[13] = 9;
	vk->vertices_index[14] = 10;
	vk->vertices_index[15] = 10;
	vk->vertices_index[16] = 11;
	vk->vertices_index[17] = 8;

	vk->vertices_index[18] = 12;
	vk->vertices_index[19] = 13;
	vk->vertices_index[20] = 14;
	vk->vertices_index[21] = 14;
	vk->vertices_index[22] = 15;
	vk->vertices_index[23] = 12;

	vk->vertices_index[24] = 16;
	vk->vertices_index[25] = 17;
	vk->vertices_index[26] = 18;
	vk->vertices_index[27] = 18;
	vk->vertices_index[28] = 19;
	vk->vertices_index[29] = 16;

	vk->vertices_index[30] = 20;
	vk->vertices_index[31] = 21;
	vk->vertices_index[32] = 22;
	vk->vertices_index[33] = 22;
	vk->vertices_index[34] = 23;
	vk->vertices_index[35] = 20;
}
