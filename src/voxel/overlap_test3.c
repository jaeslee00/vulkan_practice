/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlap_test3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:07:06 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/26 14:15:02 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "overlap_test.h"

int	axis_x_test_e0(float z_comp, float y_comp, float z_size, float y_size, float *vtx0, float *vtx2, float *half_size)
{
	float	p0;
	float	p2;
	float	rad;
	float	min;
	float	max;

	p0 = z_comp * vtx0[1] - y_comp * vtx0[2];
	p2 = z_comp * vtx2[1] - y_comp * vtx2[2];

	if (p0 < p2)
	{
		min = p0;
		max = p2;
	}
	else
	{
		min = p2;
		max = p0;
	}
	rad = z_size * half_size[1] + y_size * half_size[2];
	if (min > rad || max < -rad)
	{
		return (0); //--> doesn't overlap
	}
	return (1);
}

int	axis_y_test_e0(float z_comp, float x_comp, float z_size, float x_size, float *vtx0, float *vtx2, float *half_size)
{
	float	p0;
	float	p2;
	float	rad;
	float	min;
	float	max;

	p0 = -z_comp * vtx0[0] + x_comp * vtx0[2];
	p2 = -z_comp * vtx2[0] + x_comp * vtx2[2];

	if (p0 < p2)
	{
		min = p0;
		max = p2;
	}
	else
	{
		min = p2;
		max = p0;
	}
	rad = z_size * half_size[0] + x_size * half_size[2];
	if (min > rad || max < -rad)
	{
		return (0);
	}
	return (1);
}

int	axis_z_test_e0(float y_comp, float x_comp, float y_size, float x_size, float *vtx1, float *vtx2, float *half_size)
{
	float	p1;
	float	p2;
	float	rad;
	float	min;
	float	max;

	p1 = y_comp * vtx1[0] - x_comp * vtx1[1];
	p2 = y_comp * vtx2[0] - x_comp * vtx2[1];

	if (p1 < p2)
	{
		min = p1;
		max = p2;
	}
	else
	{
		min = p2;
		max = p1;
	}
	rad = y_size * half_size[0] + x_size * half_size[1];
	if (min > rad || max < -rad)
	{
		return (0);
	}
	return (1);
}

int	axis_x_test_e1(float z_comp, float y_comp, float z_size, float y_size, float *vtx0, float *vtx2, float *half_size)
{
	float	p0;
	float	p2;
	float	rad;
	float	min;
	float	max;

	p0 = z_comp * vtx0[1] - y_comp * vtx0[2];
	p2 = z_comp * vtx2[1] - y_comp * vtx2[2];

	if (p0 < p2)
	{
		min = p0;
		max = p2;
	}
	else
	{
		min = p2;
		max = p0;
	}
	rad = z_size * half_size[1] + y_size * half_size[2];
	if (min > rad || max < -rad)
	{
		return (0);
	}
	return (1);
}

int	axis_y_test_e1(float z_comp, float x_comp, float z_size, float x_size, float *vtx0, float *vtx2, float *half_size)
{
	float	p0;
	float	p2;
	float	rad;
	float	min;
	float	max;

	p0 = -z_comp * vtx0[0] + x_comp * vtx0[2];
	p2 = -z_comp * vtx2[0] + x_comp * vtx2[2];

	if (p0 < p2)
	{
		min = p0;
		max = p2;
	}
	else
	{
		min = p2;
		max = p0;
	}
	rad = z_size * half_size[0] + x_size * half_size[2];
	if (min > rad || max < -rad)
	{
		return (0);
	}
	return (1);
}

int	axis_z_test_e1(float y_comp, float x_comp, float y_size, float x_size, float *vtx0, float *vtx1, float *half_size)
{
	float	p0;
	float	p1;
	float	rad;
	float	min;
	float	max;

	p0 = y_comp * vtx0[0] - x_comp * vtx0[1];
	p1 = y_comp * vtx1[0] - x_comp * vtx1[1];

	if (p0 < p1)
	{
		min = p0;
		max = p1;
	}
	else
	{
		min = p1;
		max = p0;
	}
	rad = y_size * half_size[0] + x_size * half_size[1];
	if (min > rad || max < -rad)
	{
		return (0);
	}
	return (1);
}

int	axis_x_test_e2(float z_comp, float y_comp, float z_size, float y_size, float *vtx0, float *vtx1, float *half_size)
{
	float	p0;
	float	p1;
	float	rad;
	float	min;
	float	max;

	p0 = z_comp * vtx0[1] - y_comp * vtx0[2];
	p1 = z_comp * vtx1[1] - y_comp * vtx1[2];

	if (p0 < p1)
	{
		min = p0;
		max = p1;
	}
	else
	{
		min = p1;
		max = p0;
	}
	rad = z_size * half_size[1] + y_size * half_size[2];
	if (min > rad || max < -rad)
	{
		return (0);
	}
	return (1);
}

int	axis_y_test_e2(float z_comp, float x_comp, float z_size, float x_size, float *vtx0, float *vtx1, float *half_size)
{
	float	p0;
	float	p1;
	float	rad;
	float	min;
	float	max;

	p0 = z_comp * vtx0[1] - x_comp * vtx0[2];
	p1 = z_comp * vtx1[1] - x_comp * vtx1[2];

	if (p0 < p1)
	{
		min = p0;
		max = p1;
	}
	else
	{
		min = p1;
		max = p0;
	}
	rad = z_size * half_size[0] + x_size * half_size[2];
	if (min > rad || max < -rad)
	{
		return (0);
	}
	return (1);
}

int	axis_z_test_e2(float y_comp, float x_comp, float y_size, float x_size, float *vtx1, float *vtx2, float *half_size)
{
	float	p1;
	float	p2;
	float	rad;
	float	min;
	float	max;

	p1 = y_comp * vtx1[0] - x_comp * vtx1[1];
	p2 = y_comp * vtx2[0] - x_comp * vtx2[1];

	if (p1 < p2)
	{
		min = p1;
		max = p2;
	}
	else
	{
		min = p2;
		max = p1;
	}
	rad = y_size * half_size[0] + x_size * half_size[1];
	if (min > rad || max < -rad)
	{
		return (0);
	}
	return (1);
}

