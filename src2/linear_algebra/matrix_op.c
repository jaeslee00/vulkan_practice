/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 01:05:53 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/10 14:43:57 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	mat4_multiply(float *dst, float *mat1, float *mat2)
{
	int	row_dst;
	int	row;
	int	col;

	row = 0;
	while (row < 4)
	{
		col = 0;
		row_dst = row * 4;
		while (col < 4)
		{
			dst[row_dst + col] =
			(mat1[row_dst + 0] * mat2[col + 4 * 0]) +
			(mat1[row_dst + 1] * mat2[col + 4 * 1]) +
			(mat1[row_dst + 2] * mat2[col + 4 * 2]) +
			(mat1[row_dst + 3] * mat2[col + 4 * 3]);
			col++;
		}
		row++;
	}
}

void	mat4_identity(float *mat)
{
	ft_bzero(mat, sizeof(float) * 16);
	mat[0] = 1.0f;
	mat[5] = 1.0f;
	mat[10] = 1.0f;
	mat[15] = 1.0f;
}

/*TODO if possible SIMD */
//void	rotate_x_axis(); // order?
//void	rotate_y_axis(); // order?
//void	rotate_z_axis(); // order?

//void	scale_mat();
//void	perspective_mat(); // distortion from distance + clipping
//void	orthogonal_mat(); // no distortion from distance + clipping
