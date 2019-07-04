/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 11:22:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/07/03 21:54:10 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxel.h"

int	main(void)
{
	t_voxel	init_voxel;
	t_octree *root;
	ft_bzero(init_voxel.center, sizeof(float) * 3);
	init_voxel.min_dist = 0.0f;
	init_voxel.size = 2.0f;

	root = init_octree(&init_voxel, sizeof(t_voxel));
	voxel_create(root);
	for (int j=0; j < 8; j++)
		voxel_create(&(root->children[j]));
	for (int k=0; k < 8; k++)
	{
		for (int i=0; i < 8; i++)
		{
			printf("%f %f %f\n", ((t_voxel*)root->children[k].children[i].content)->center[0],
			((t_voxel*)root->children[k].children[i].content)->center[1],
			((t_voxel*)root->children[k].children[i].content)->center[2]);
		}
	}
}

/* used RGBA !
	BFS through the voxel space to order the voxel into continuous data structure

	RGB : triplets to express sub voxels of a voxel
	A : A == 1 => data is stored in a cell
		A == 0 => empty cell
		A == 2 => index to sub_voxel

(0, 0, 0) == root
()

