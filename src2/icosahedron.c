/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icosahedron.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:54:27 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/06 23:09:02 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	get_icosahedron(t_vulkan *vk)

{
	float	t;
	t_vertex	tri_vtx;
	t = (1.0f + sqrtf(5.0f)) / 2.0f;
	array_init(&vk->ico, sizeof(t_vertex));
	add_vertex(&vk->ico, &tri_vtx, -1.0f, t, 0.0f,
								1.0f, 0.0f, 1.0f,
								1.0f, 1.0f);
	add_vertex(&vk->ico, &tri_vtx, 1.0f, t, 0.0f,
								1.0f, 0.0f, 0.0f,
								0.0f, 0.0f);
	add_vertex(&vk->ico, &tri_vtx, -1.0f, -t, 0.0f,
								0.0f, 1.0f, 1.0f,
								0.0f, 0.0f);
	add_vertex(&vk->ico, &tri_vtx, 1.0f, -t, 0.0f,
								0.0f, 0.0f, 1.0f,
								1.0f, 1.0f);

	add_vertex(&vk->ico, &tri_vtx, 0.0f, -1.f, t,
								1.0f, 0.0f, 1.0f,
								0.0f, 0.0f);
	add_vertex(&vk->ico, &tri_vtx, 0.0f, 1.f, t,
								1.0f, 0.0f, 0.0f,
								0.0f, 1.0f);
	add_vertex(&vk->ico, &tri_vtx, 0.0f, -1.f, -t,
								0.0f, 1.0f, 0.0f,
								0.0f, 0.0f);
	add_vertex(&vk->ico, &tri_vtx, 0.0f, 1.f, -t,
								0.0f, 0.0f, 1.0f,
								1.0f, 0.0f);

	add_vertex(&vk->ico, &tri_vtx, t, 0, -1.f,
								1.0f, 0.0f, 1.0f,
								0.0f, 1.0f);
	add_vertex(&vk->ico, &tri_vtx, t, 0, 1.f,
								1.0f, 0.0f, 1.0f,
								0.0f, 0.0f);
	add_vertex(&vk->ico, &tri_vtx, -t, 0, -1.f,
								1.0f, 0.0f, 1.0f,
								0.0f, 1.0f);
	add_vertex(&vk->ico, &tri_vtx, -t, 0, 1.f,
								1.0f, 0.0f, 1.0f,
								1.0f, 0.0f);

	vk->vertices_index = (uint32_t*)malloc(60 * sizeof(uint32_t));
	ft_bzero(vk->vertices_index, sizeof(uint32_t) * 60);

	vk->vertices_index[0] = 0;
	vk->vertices_index[1] = 11;
	vk->vertices_index[2] = 5;

	vk->vertices_index[3] = 5;
	vk->vertices_index[4] = 1;
	vk->vertices_index[5] = 0;

	vk->vertices_index[6] = 0;
	vk->vertices_index[7] = 1;
	vk->vertices_index[8] = 7;

	vk->vertices_index[9] = 7;
	vk->vertices_index[10] = 10;
	vk->vertices_index[11] = 0;

	vk->vertices_index[12] = 0;
	vk->vertices_index[13] = 10;
	vk->vertices_index[14] = 11;
///////////////////////////////////////////////////////
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
////////////////////////////////////////////////////
	vk->vertices_index[30] = 3;
	vk->vertices_index[31] = 9;
	vk->vertices_index[32] = 4;

	vk->vertices_index[33] = 4;
	vk->vertices_index[34] = 2;
	vk->vertices_index[35] = 3;

	vk->vertices_index[36] = 3;
	vk->vertices_index[37] = 2;
	vk->vertices_index[38] = 6;

	vk->vertices_index[39] = 6;
	vk->vertices_index[40] = 8;
	vk->vertices_index[41] = 3;

	vk->vertices_index[42] = 3;
	vk->vertices_index[43] = 8;
	vk->vertices_index[44] = 9;
///////////////////////////////////////////////////
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

	vk->vi = (uint32_t*)malloc(240 * sizeof(uint32_t));
	vk->new_vi = (uint32_t*)malloc(960 * sizeof(uint32_t));
	vk->final_vi = (uint32_t*)malloc(3840 * sizeof(uint32_t));
	refine_icosahedron(vk, &vk->ico, vk->vertices_index, vk->vi, 58);
	free(vk->vertices_index);
	refine_icosahedron(vk, &vk->ico, vk->vi, vk->new_vi, 238);
	free(vk->vi);
	refine_icosahedron(vk, &vk->ico, vk->new_vi, vk->final_vi, 958);
	free(vk->new_vi);
}

void	get_midpoint(float *mid_vtx, float *vtx1, float *vtx2)
{
	float	scale;

	mid_vtx[0] = (vtx1[0] + vtx2[0]);
	mid_vtx[1] = (vtx1[1] + vtx2[1]);
	mid_vtx[2] = (vtx1[2] + vtx2[2]);
	vec3_normalize(mid_vtx);
}

void	refine_icosahedron(t_vulkan *vk, t_array *ico, uint32_t *vtx_index, uint32_t *new_vtx_index, int refine)
{
	t_vertex	*old_vtx;
	t_vertex	new_vtx;
	float		mid_vertex_a[3];
	float		mid_vertex_b[3];
	float		mid_vertex_c[3];
	int			i;
	int 		ico_vertices;

	ico_vertices = ico->length;

	i = 0;
	while (i < refine)
	{
		old_vtx = (t_vertex*)vk->ico.ptr;
		get_midpoint(mid_vertex_a, old_vtx[vtx_index[i]].pos, old_vtx[vtx_index[i + 1]].pos);
		get_midpoint(mid_vertex_b, old_vtx[vtx_index[i + 1]].pos, old_vtx[vtx_index[i + 2]].pos);
		get_midpoint(mid_vertex_c, old_vtx[vtx_index[i + 2]].pos, old_vtx[vtx_index[i]].pos);

		add_vertex(&vk->ico, &new_vtx, mid_vertex_a[0], mid_vertex_a[1], mid_vertex_a[2],
			0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
		add_vertex(&vk->ico, &new_vtx, mid_vertex_b[0], mid_vertex_b[1], mid_vertex_b[2],
			0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
		add_vertex(&vk->ico, &new_vtx, mid_vertex_c[0], mid_vertex_c[1], mid_vertex_c[2],
			1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

		new_vtx_index[i * 4] = vtx_index[i];
		new_vtx_index[i * 4 + 1] = ico_vertices + i;
		new_vtx_index[i * 4 + 2] = ico_vertices + (i + 2);

		new_vtx_index[i * 4 + 3] = vtx_index[i + 1];
		new_vtx_index[i * 4 + 4] = ico_vertices + (i + 1);
		new_vtx_index[i * 4 + 5] = ico_vertices + i;

		new_vtx_index[i * 4 + 6] = vtx_index[i + 2];
		new_vtx_index[i * 4 + 7] = ico_vertices + (i + 2);
		new_vtx_index[i * 4 + 8] = ico_vertices + (i + 1);

		new_vtx_index[i * 4 + 9] = ico_vertices + i;
		new_vtx_index[i * 4 + 10] = ico_vertices + (i + 2);
		new_vtx_index[i * 4 + 11] = ico_vertices + (i + 1);

		i += 3;
	}
}
