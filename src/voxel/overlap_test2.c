/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlap_test2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 16:09:25 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/26 14:07:01 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "overlap_test.h"

int		plane_box_test(float *normal, float *vtx, float *half_size)
{
	int		dim;
	float	min[3];
	float	max[3];

	dim = 0;
	while (dim < 3)
	{
		if (normal[dim] > 0.0f)
		{
			min[dim] = -half_size[dim] - vtx[dim];
			max[dim] = half_size[dim] - vtx[dim];
		}
		else if(normal[dim] < 0.0f)
		{
			min[dim] = half_size[dim] - vtx[dim];
			max[dim] = -half_size[dim] - vtx[dim];
		}
		dim++;
	}
	if (vec3_dot(normal, min) > 0.0f)
		return (0);
	if (vec3_dot(normal, max) > 0.0f)
		return (1);
	return (0);
}
