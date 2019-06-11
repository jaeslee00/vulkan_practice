/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icosahedron.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 18:54:27 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/10 18:44:12 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	get_icosahedron(t_vulkan *vk)

{
	float		t;

	t = (1.0f + sqrtf(5.0f)) / 2.0f;
	array_init(&vk->vtx, sizeof(t_vertex_info));
	add_vertex(vk, (float[]){-1.0f, t, 0.0f}, 1.0f, 1.0f, 1.0f);
	add_vertex(vk, (float[]){1.0f, t, 0.0f}, 1.0f, 1.0f, 1.0f);
	add_vertex(vk, (float[]){-1.0f, -t, 0.0f}, 1.0f, 1.0f, 1.0f);
	add_vertex(vk, (float[]){1.0f, -t, 0.0f}, 1.0f, 1.0f, 1.0f);

	add_vertex(vk, (float[]){0.0f, -1.f, t}, 1.0f, 1.0f, 1.0f);
	add_vertex(vk, (float[]){0.0f, 1.f, t}, 1.0f, 1.0f, 1.0f);
	add_vertex(vk, (float[]){0.0f, -1.f, -t}, 1.0f, 1.0f, 1.0f);
	add_vertex(vk, (float[]){0.0f, 1.f, -t}, 1.0f, 1.0f, 1.0f);

	add_vertex(vk, (float[]){t, 0, -1.f}, 1.0f, 1.0f, 1.0f);
	add_vertex(vk, (float[]){t, 0, 1.f}, 1.0f, 1.0f, 1.0f);
	add_vertex(vk, (float[]){-t, 0, -1.f}, 1.0f, 1.0f, 1.0f);
	add_vertex(vk, (float[]){-t, 0, 1.f}, 1.0f, 1.0f, 1.0f);

	array_init(&vk->tri_faces, sizeof(t_tri_vtx_indices));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){0, 11, 5}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){5, 1, 0}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){0, 1, 7}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){7, 10, 0}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){0, 10, 11}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){1, 5, 9}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){5, 11, 4}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){11, 10, 2}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){10, 7 ,6}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){7, 1, 8}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){3, 9, 4}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){4, 2, 3}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){3, 2, 6}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){6, 8, 3}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){3, 8, 9}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){4, 9, 5}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){2, 4, 11}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){6, 2, 10}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){8, 6, 7}));
	array_push_back(&vk->tri_faces, &((t_tri_vtx_indices){9, 8, 1}));

	refine_icosahedron(vk, 6);
	printf("%zu\n", vk->vtx.length);
}

int			pair_compare(const void *content1, const void *content2)
{
	if ( ((t_pair*)content1)->pair != ((t_pair*)content2)->pair )
		return (1);
	return (0);
}

uint32_t	add_midpoint(t_vulkan *vk, uint32_t v1, uint32_t v2)
{
	float		mid_vertex[3];
	size_t		index;
	t_tree		*new_node;
	t_tree		*node;
	t_pair		vtx_pair;
	uint32_t	minor;
	uint32_t	major;

	minor = v1 > v2 ? v2 : v1;
	major = v1 > v2 ? v1 : v2;
	ft_bzero(&vtx_pair, sizeof(t_pair));
	vtx_pair.pair |= ((uint64_t)minor << 32);
	vtx_pair.pair |= (uint64_t)major;
	index = 0;
	if ((node = tree_search(vk->pair_tree, &vtx_pair, pair_compare)) != NULL)
	{
		return (((t_pair*)node->content)->vtx_index);
	}
	else
	{
		mid_vertex[0] = (((t_vertex_info*)vk->vtx.ptr)[minor].pos[0]
			+ ((t_vertex_info*)vk->vtx.ptr)[major].pos[0]);
		mid_vertex[1] = (((t_vertex_info*)vk->vtx.ptr)[minor].pos[1]
			+ ((t_vertex_info*)vk->vtx.ptr)[major].pos[1]);
		mid_vertex[2] = (((t_vertex_info*)vk->vtx.ptr)[minor].pos[2]
			+ ((t_vertex_info*)vk->vtx.ptr)[major].pos[2]);
		vtx_pair.vtx_index = add_vertex(vk, mid_vertex, 0.0f, 0.0f, 0.0f);
		tree_insert(&vk->pair_tree, node_create(&vtx_pair, sizeof(t_pair)), pair_compare);
		return (vtx_pair.vtx_index);
	}
}

void		refine_icosahedron(t_vulkan *vk, int refine)
{
	size_t				i;
	int					refine_index;
	size_t				a;
	size_t				b;
	size_t				c;
	t_array				tmp_faces;
	t_tri_vtx_indices	triangle;

	refine_index = 0;
	vk->pair_tree = NULL;
	while (refine_index < refine)
	{
		array_init(&tmp_faces, sizeof(t_tri_vtx_indices));
		i = 0;
		while (i < vk->tri_faces.length)
		{
			triangle = ((t_tri_vtx_indices*)vk->tri_faces.ptr)[i];
			a = add_midpoint(vk, triangle.v1, triangle.v2);
			b = add_midpoint(vk, triangle.v2, triangle.v3);
			c = add_midpoint(vk, triangle.v3, triangle.v1);
			array_push_back(&tmp_faces, &((t_tri_vtx_indices){a, b, c}));
			array_push_back(&tmp_faces, &((t_tri_vtx_indices){triangle.v1, a, c}));
			array_push_back(&tmp_faces, &((t_tri_vtx_indices){triangle.v2, b, a}));
			array_push_back(&tmp_faces, &((t_tri_vtx_indices){triangle.v3, c, b}));
			i++;
		}
		array_clear(&vk->tri_faces, NULL);
		vk->tri_faces.ptr = tmp_faces.ptr;
		vk->tri_faces.length = tmp_faces.length;
		vk->tri_faces.reserved = tmp_faces.reserved;
		ft_bzero(&tmp_faces, sizeof(t_array));
		refine_index++;
	}
}
