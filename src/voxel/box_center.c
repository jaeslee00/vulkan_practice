/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_center.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:58:59 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/30 21:57:21 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxel.h"

void	voxel_center0(short child_index, float new_center[3], float center[3],
			float new_voxel_size)
{
	new_center[0] = center[0] + new_voxel_size * 0.5f;
	new_center[1] = center[1] + new_voxel_size * 0.5f;
	new_center[2] = center[2] + new_voxel_size * 0.5f;
}

void	voxel_center1(short child_index, float new_center[3], float center[3],
			float new_voxel_size)
{
	new_center[0] = center[0] - new_voxel_size * 0.5f;
	new_center[1] = center[1] + new_voxel_size * 0.5f;
	new_center[2] = center[2] + new_voxel_size * 0.5f;
}

void	voxel_center2(short child_index, float new_center[3], float center[3],
			float new_voxel_size)
{
	new_center[0] = center[0] + new_voxel_size * 0.5f;
	new_center[1] = center[1] - new_voxel_size * 0.5f;
	new_center[2] = center[2] + new_voxel_size * 0.5f;
}

void	voxel_center3(short child_index, float new_center[3], float center[3],
			float new_voxel_size)
{
	new_center[0] = center[0] + new_voxel_size * 0.5f;
	new_center[1] = center[1] + new_voxel_size * 0.5f;
	new_center[2] = center[2] - new_voxel_size * 0.5f;
}

void	voxel_center4(short child_index, float new_center[3], float center[3],
			float new_voxel_size)
{
	new_center[0] = center[0] - new_voxel_size * 0.5f;
	new_center[1] = center[1] - new_voxel_size * 0.5f;
	new_center[2] = center[2] + new_voxel_size * 0.5f;
}

void	voxel_center5(short child_index, float new_center[3], float center[3],
			float new_voxel_size)
{
	new_center[0] = center[0] + new_voxel_size * 0.5f;
	new_center[1] = center[1] - new_voxel_size * 0.5f;
	new_center[2] = center[2] - new_voxel_size * 0.5f;
}

void	voxel_center6(short child_index, float new_center[3], float center[3],
			float new_voxel_size)
{
	new_center[0] = center[0] - new_voxel_size * 0.5f;
	new_center[1] = center[1] + new_voxel_size * 0.5f;
	new_center[2] = center[2] - new_voxel_size * 0.5f;
}

void	voxel_center7(short child_index, float new_center[3], float center[3],
			float new_voxel_size)
{
	new_center[0] = center[0] - new_voxel_size * 0.5f;
	new_center[1] = center[1] - new_voxel_size * 0.5f;
	new_center[2] = center[2] - new_voxel_size * 0.5f;
}
