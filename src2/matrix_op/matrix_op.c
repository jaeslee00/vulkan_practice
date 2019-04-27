/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 01:05:53 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/27 02:16:02 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	mat_mul(float *dst, float *mat1, float *mat2, size_t size)
{
	size_t	row;
	size_t	col;
	size_t	row_dst;

	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			row_dst = 0;
			dst[row * size + col] = 0;
			while (row_dst < size)
			{
				dst[row * size + col] +=
					mat1[row * size + row_dst] * mat2[row_dst * size + col];
				row_dst++;
			}
			col++;
		}
		row++;
	}
}

void	mat_add(float *dst, float *mat1, float *mat2, size_t size)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			dst[row * size + col] =
				mat1[row * size + col] + mat2[row * size + col];
			col++;
		}
		row++;
	}
}

void	mat_sub(float *dst, float *mat1, float *mat2, size_t size)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < size)
	{
		col = 0;
		while (col < size)
		{
			dst[row * size + col] =
				mat1[row * size + col] - mat2[row * size + col];
			col++;
		}
		row++;
	}
}
