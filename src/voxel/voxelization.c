/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 15:20:26 by jaelee            #+#    #+#             */
/*   Updated: 2019/07/01 14:38:05 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxel.h"

void	(*const g_voxel_center_fn[8])(short, float[3], float[3], float) = {
	voxel_center0,
	voxel_center1,
	voxel_center2,
	voxel_center3,
	voxel_center4,
	voxel_center5,
	voxel_center6,
	voxel_center7
};

t_octree	*init_octree(void *content, size_t content_size)
{
	t_octree	*root;
	t_voxel		new_node;

	root = (t_octree*)ft_memalloc(sizeof(t_octree));
	if (content && content_size > 0)
	{
		if (!(root->content = malloc(content_size)))
			return (NULL);
		root->parent = NULL;
		root->children = NULL;
		ft_memcpy(root->content, content, content_size);
		root->content_size = content_size;

		return (root);
	}
	return (0);
}

int		octree_create(t_octree *parent, void *content, size_t total_size)
{
	t_octree	*new_node;
	t_voxel		*child;
	size_t		content_size;
	short		index;

	content_size = total_size / 8;
	if (parent == NULL)
	{
		printf("initialize octree!\n");
		return (-1);
	}
	if (parent != NULL)
	{
		if (!(parent->children = (t_octree*)malloc(8 * sizeof(t_octree))))
			return (-1);
		index = 0;
		while (index < 8)
		{
			new_node = &(parent->children[index]);
			new_node->parent = parent;
			new_node->children = NULL;
			new_node->content = ft_memalloc(content_size);
			child = (t_voxel*)(content + (content_size * index));
			ft_memcpy(new_node->content, child, content_size);
			new_node->content_size = content_size;
			index++;
		}
		return (1);
	}
	return (-1);
}

void	voxel_create(t_octree *parent)
{
	float	*center;
	float	new_voxel_size;
	short	child_index;
	t_voxel	children[8];

	if (!parent)
		return ;
	center = ((t_voxel*)parent->content)->center;
	new_voxel_size = ((t_voxel*)parent->content)->size * 0.5f;

	child_index = 0;
	while (child_index < 8)
	{
		children[child_index].size = new_voxel_size;
		children[child_index].min_dist = 0.0f;
		g_voxel_center_fn[child_index](child_index,
			children[child_index].center, center, new_voxel_size);
		child_index++;
	}
	octree_create(parent, children, sizeof(t_voxel) * 8);
}
