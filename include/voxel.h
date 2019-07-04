/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 21:08:35 by jaelee            #+#    #+#             */
/*   Updated: 2019/07/01 14:20:52 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOXEL_H
# define VOXEL_H

# include "libft.h"
# include <stdint.h>
# include <math.h>

typedef struct s_voxel
{
	float	center[3];
	float	min_dist;
	float	size;
}				t_voxel;

typedef struct	s_octree
{
	struct	s_octree *parent;
	struct	s_octree *children;
	void	*content;
	size_t	content_size;
}				t_octree;

t_octree	*init_octree(void *content, size_t content_size);
int			octree_create(t_octree *parent, void *content, size_t total_size);

void	voxel_create(t_octree *parent);

void	voxel_center0(short child_index, float new_center[3],
			float old_center[3], float new_voxel_size);
void	voxel_center1(short child_index, float new_center[3],
			float old_center[3], float new_voxel_size);
void	voxel_center2(short child_index, float new_center[3],
			float old_center[3], float new_voxel_size);
void	voxel_center3(short child_index, float new_center[3],
			float old_center[3], float new_voxel_size);
void	voxel_center4(short child_index, float new_center[3],
			float old_center[3], float new_voxel_size);
void	voxel_center5(short child_index, float new_center[3],
			float old_center[3], float new_voxel_size);
void	voxel_center6(short child_index, float new_center[3],
			float old_center[3], float new_voxel_size);
void	voxel_center7(short child_index, float new_center[3],
			float old_center[3], float new_voxel_size);


#endif
