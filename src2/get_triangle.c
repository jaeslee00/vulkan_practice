/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 02:38:05 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/03 10:31:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "vector.h"

void	get_vtx_info(t_array *triangle, t_vertex *vertex, float vtx1, float vtx2, float vtx3,
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
	array_push_back(triangle, vertex);
}


void	sphere_transformation(float *out, float *src)
{
	out[0] = src[0] * sqrtf(1.0 - (src[1]*src[1]/2.0) - (src[2]*src[2]/2.0) + (src[1]*src[1]*src[2]*src[2]/3.0));
	out[1]= src[1] * sqrtf(1.0 - (src[2]*src[2]/2.0) - (src[0]*src[0]/2.0) + (src[2]*src[2]*src[0]*src[0]/3.0));
	out[2] = src[2] * sqrtf(1.0 - (src[0]*src[0]/2.0) - (src[1]*src[1]/2.0) + (src[0]*src[0]*src[1]*src[1]/3.0));
	vec3_normalize(out);
	vec3_scale(out, .7f);
}

void	get_cube_info(t_vulkan *vk)
{
	t_vertex	tri_vtx;
	float		quad;
	float		out[3];
	float		in[3];
	float		x = -0.5f;
	float		y = 0.5f;
	float		z = 0.5f;
	float		divisor;

	divisor = 512.0f;
	quad = 1.f / divisor;
	array_init(&vk->triangle, sizeof(t_vertex));

	for (int j=0; j < (int)divisor; j++)
	{
		y = 0.5f;
		for (int t=0; t < (int)divisor; t++)
		{
			sphere_transformation(out, (float[]){x, y, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x + quad, y, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x + quad, y - quad, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x, y - quad, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
			y = y - quad;
		}
		x = x + quad;
	}
	x = -0.5f;
	y = 0.5f;
	z = -0.5f;
	for (int k=0; k < (int)divisor; k++)
	{
		y = 0.5f;
		for (int n=0; n < (int)divisor; n++)
		{
			sphere_transformation(out, (float[]){x, y, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x + quad, y, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x + quad, y - quad, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x, y - quad, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
			y = y - quad;
		}
		x = x + quad;
	}
///////////////////////TOP BOTTOM//////////////////////////////
	x = -0.5f;
	y = 0.5f;
	z = 0.5f;
	for (int k=0; k < (int)divisor; k++)
	{
		z = 0.5f;
		for (int n=0; n < (int)divisor; n++)
		{
			sphere_transformation(out, (float[]){x, y, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x + quad, y, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x + quad, y, z - quad});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x, y, z - quad});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
			z = z - quad;
		}
		x = x + quad;
	}
	x = -0.5f;
	y = -0.5f;
	z = 0.5f;
	for (int k=0; k < (int)divisor; k++)
	{
		z = 0.5f;
		for (int n=0; n < (int)divisor; n++)
		{
			sphere_transformation(out, (float[]){x, y, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
//			array_push_back(&vk->triangle, &tri_vtx);
			sphere_transformation(out, (float[]){x + quad, y, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
//			array_push_back(&vk->triangle, &tri_vtx);
			sphere_transformation(out, (float[]){x + quad, y, z - quad});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
//			array_push_back(&vk->triangle, &tri_vtx);
			sphere_transformation(out, (float[]){x, y, z - quad});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
//			array_push_back(&vk->triangle, &tri_vtx);
			z = z - quad;
		}
		x = x + quad;
	}
////////////////////LEFT-RIGHT/////////////////////////
	x = 0.5f;
	y = 0.5f;
	z = 0.5f;
	for (int k=0; k < (int)divisor; k++)
	{
		z = 0.5f;
		for (int n=0; n < (int)divisor; n++)
		{
			sphere_transformation(out, (float[]){x, y, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x, y - quad, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x, y - quad, z - quad});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x, y, z - quad});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
			z = z - quad;
		}
		y = y - quad;
	}
	x = -0.5f;
	y = 0.5f;
	z = 0.5f;
	for (int k=0; k < (int)divisor; k++)
	{
		z = 0.5f;
		for (int n=0; n < (int)divisor; n++)
		{
			sphere_transformation(out, (float[]){x, y, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x, y - quad, z});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x, y - quad, z - quad});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			sphere_transformation(out, (float[]){x, y, z - quad});
			get_vtx_info(&vk->triangle, &tri_vtx, out[0], out[1], out[2], 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
			z = z - quad;
		}
		y = y - quad;
	}

	vk->vertices_index = (uint32_t*)malloc(262144 * 6 * 6 * sizeof(uint32_t));
	for (int i=0; i < 262144 * 6; i++)
	{
		vk->vertices_index[0 + i * 6] = 0 + 4 * i;
		vk->vertices_index[1 + i * 6] = 1 + 4 * i;
		vk->vertices_index[2 + i * 6] = 2 + 4 * i;
		vk->vertices_index[3 + i * 6] = 2 + 4 * i;
		vk->vertices_index[4 + i * 6] = 3 + 4 * i;
		vk->vertices_index[5 + i * 6] = 0 + 4 * i;
	}
}
/*
void	get_triangle_info(t_vulkan *vk)
{
	t_vertex	tri_vtx;
	float		cube_size;
	float		out[3];

	cube_size = 0.5f;

	array_init(&vk->triangle, sizeof(t_vertex));

	get_vtx_info(&tri_vtx, -cube_size, -cube_size, -cube_size, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, cube_size, -cube_size, -cube_size, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, cube_size, cube_size, -cube_size, 0.0f, 0.0f, 1.0f, 2.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -cube_size, cube_size, -cube_size, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);


	get_vtx_info(&tri_vtx, -cube_size, -cube_size, cube_size, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, cube_size, -cube_size, cube_size, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, cube_size, cube_size, cube_size, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -cube_size, cube_size, cube_size, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);


	get_vtx_info(&tri_vtx, -cube_size, -cube_size, cube_size, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -cube_size, -cube_size, -cube_size, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, cube_size, -cube_size, -cube_size, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, cube_size, -cube_size, cube_size, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);


	get_vtx_info(&tri_vtx, cube_size, cube_size, -cube_size, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, cube_size, cube_size, cube_size, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -cube_size, cube_size, cube_size, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -cube_size, cube_size, -cube_size, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);


	get_vtx_info(&tri_vtx, cube_size, -cube_size, -cube_size, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, cube_size, -cube_size, cube_size, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, cube_size, cube_size, cube_size, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, cube_size, cube_size, -cube_size, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);


	get_vtx_info(&tri_vtx, -cube_size, cube_size, cube_size, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -cube_size, cube_size, -cube_size, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -cube_size, -cube_size, -cube_size, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);
	get_vtx_info(&tri_vtx, -cube_size, -cube_size, cube_size, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	array_push_back(&vk->triangle, &tri_vtx);

	vk->vertices_index = (uint32_t*)malloc(65536 * 6 * 6 * sizeof(uint32_t));
	for (int i=0; i < 256 * 6; i++)
	{
		vk->vertices_index[0 + i * 6] = 0 + 4 * i;
		vk->vertices_index[1 + i * 6] = 1 + 4 * i;
		vk->vertices_index[2 + i * 6] = 2 + 4 * i;
		vk->vertices_index[3 + i * 6] = 2 + 4 * i;
		vk->vertices_index[4 + i * 6] = 3 + 4 * i;
		vk->vertices_index[5 + i * 6] = 0 + 4 * i;
	}

	// vk->vertices_index = (uint32_t*)malloc(32 * sizeof(uint32_t));
	// vk->vertices_index[0] = 0;
	// vk->vertices_index[1] = 1;
	// vk->vertices_index[2] = 2;
	// vk->vertices_index[3] = 2;
	// vk->vertices_index[4] = 3;
	// vk->vertices_index[5] = 0;

	// vk->vertices_index[6] = 4;
	// vk->vertices_index[7] = 5;
	// vk->vertices_index[8] = 6;
	// vk->vertices_index[9] = 6;
	// vk->vertices_index[10] = 7;
	// vk->vertices_index[11] = 4;

	// vk->vertices_index[12] = 8;
	// vk->vertices_index[13] = 9;
	// vk->vertices_index[14] = 10;
	// vk->vertices_index[15] = 10;
	// vk->vertices_index[16] = 11;
	// vk->vertices_index[17] = 8;

	// vk->vertices_index[18] = 12;
	// vk->vertices_index[19] = 13;
	// vk->vertices_index[20] = 14;
	// vk->vertices_index[21] = 14;
	// vk->vertices_index[22] = 15;
	// vk->vertices_index[23] = 12;

	// vk->vertices_index[24] = 16;
	// vk->vertices_index[25] = 17;
	// vk->vertices_index[26] = 18;
	// vk->vertices_index[27] = 18;
	// vk->vertices_index[28] = 19;
	// vk->vertices_index[29] = 16;

	// vk->vertices_index[30] = 20;
	// vk->vertices_index[31] = 21;
	// vk->vertices_index[32] = 22;
	// vk->vertices_index[33] = 22;
	// vk->vertices_index[34] = 23;
	// vk->vertices_index[35] = 20;
}
*/
