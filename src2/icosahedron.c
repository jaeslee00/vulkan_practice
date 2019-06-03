/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icosahedron.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:54:27 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/03 23:30:59 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	get_icosahedron(t_vulkan *vk)

{
	float	t;
	t_vertex	tri_vtx;

	t = (1.0f + sqrtf(5.0f)) / 2.0f;
	array_init(&vk->triangle, sizeof(t_vertex));
	get_vtx_info(&vk->triangle, &tri_vtx, -1.0f, t, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	get_vtx_info(&vk->triangle, &tri_vtx, 1.0f, t, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	get_vtx_info(&vk->triangle, &tri_vtx, -1.0f, -t, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	get_vtx_info(&vk->triangle, &tri_vtx, 1.0f, -t, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);

	get_vtx_info(&vk->triangle, &tri_vtx, 0.0f, -1.f, t, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	get_vtx_info(&vk->triangle, &tri_vtx, 0.0f, 1.f, t, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	get_vtx_info(&vk->triangle, &tri_vtx, 0.0f, -1.f, -t, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	get_vtx_info(&vk->triangle, &tri_vtx, 0.0f, 1.f, -t, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);

	get_vtx_info(&vk->triangle, &tri_vtx, t, 0, -1.f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	get_vtx_info(&vk->triangle, &tri_vtx, t, 0, 1.f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	get_vtx_info(&vk->triangle, &tri_vtx, -t, 0, -1.f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	get_vtx_info(&vk->triangle, &tri_vtx, -t, 0, 1.f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);

	vk->vertices_index = (uint32_t*)malloc(60 * sizeof(uint32_t));

	vk->vertices_index[0] = 0;
	vk->vertices_index[1] = 11;
	vk->vertices_index[2] = 5;

	vk->vertices_index[3] = 0;
	vk->vertices_index[4] = 5;
	vk->vertices_index[5] = 1;

	vk->vertices_index[6] = 0;
	vk->vertices_index[7] = 1;
	vk->vertices_index[8] = 7;

	vk->vertices_index[9] = 0;
	vk->vertices_index[10] = 7;
	vk->vertices_index[11] = 10;

	vk->vertices_index[12] = 0;
	vk->vertices_index[13] = 10;
	vk->vertices_index[14] = 11;

	vk->vertices_index[15] = 1;
	vk->vertices_index[16] = 5;
	vk->vertices_index[17] = 9;

	vk->vertices_index[18] = 5;
	vk->vertices_index[19] = 11;
	vk->vertices_index[20] = 4;

	vk->vertices_index[21] = 11;
	vk->vertices_index[22] = 10;
	vk->vertices_index[23] = 2;

	vk->vertices_index[24] = 10;
	vk->vertices_index[25] = 7;
	vk->vertices_index[26] = 6;

	vk->vertices_index[27] = 7;
	vk->vertices_index[28] = 1;
	vk->vertices_index[29] = 8;

	vk->vertices_index[30] = 3;
	vk->vertices_index[31] = 9;
	vk->vertices_index[32] = 4;

	vk->vertices_index[33] = 3;
	vk->vertices_index[34] = 4;
	vk->vertices_index[35] = 2;

	vk->vertices_index[36] = 3;
	vk->vertices_index[37] = 2;
	vk->vertices_index[38] = 6;

	vk->vertices_index[39] = 3;
	vk->vertices_index[40] = 6;
	vk->vertices_index[41] = 8;

	vk->vertices_index[42] = 3;
	vk->vertices_index[43] = 8;
	vk->vertices_index[44] = 9;

	vk->vertices_index[45] = 4;
	vk->vertices_index[46] = 9;
	vk->vertices_index[47] = 5;

	vk->vertices_index[48] = 2;
	vk->vertices_index[49] = 4;
	vk->vertices_index[50] = 11;

	vk->vertices_index[51] = 6;
	vk->vertices_index[52] = 2;
	vk->vertices_index[53] = 10;

	vk->vertices_index[54] = 8;
	vk->vertices_index[55] = 6;
	vk->vertices_index[56] = 7;

	vk->vertices_index[57] = 9;
	vk->vertices_index[58] = 8;
	vk->vertices_index[59] = 1;
	printf("vertex buffer %zu\n", vk->triangle.length);
}
/* TODO refining icosahedron to morph into real spherical shape */
void computeHalfVertex(const float v1[3], const float v2[3], float newV[3])
{
    newV[0] = v1[0] + v2[0];    // x
    newV[1] = v1[1] + v2[1];    // y
    newV[2] = v1[2] + v2[2];    // z
    float scale = radius / sqrtf(newV[0]*newV[0] + newV[1]*newV[1] + newV[2]*newV[2]);
    newV[0] *= scale;
    newV[1] *= scale;
    newV[2] *= scale;
}
