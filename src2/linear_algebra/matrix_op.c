/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 01:05:53 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/30 15:35:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	mat4_mul(float *dst, float *mat1, float *mat2)
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

void	identity_mat4(float *mat)
{
	ft_bzero(mat, sizeof(float) * 16);
	mat[0] = 1;
	mat[5] = 1;
	mat[10] = 1;
	mat[15] = 1;
}

void	translation_mat4(float *mat, float x_axis, float y_axis, float z_axis)
{
	identity_mat4(mat);
	mat[0 + 3 * 1] += x_axis;
	mat[1 + 3 * 2] += y_axis;
	mat[2 + 3 * 3] += z_axis;
}

void	rotation_mat4(float *mat, float x_axis, float y_axis)
{

}

void	scaling_mat4(float *mat, float scale)
{
	identity_mat4(mat);
	mat[0] *= scale;
	mat[5] *= scale;
	mat[10] *= scale;
}

void	rotation_vec3(float *vec)
{

}

int main()
{
	float a[16] = {
		1, 3, 5, 7,
		2, 7, 9, 1,
		1, 8, 9, 5,
		4, 8, 3, 3
	};
	float b[16] = {
		1, 3, 5, 7,
		2, 7, 9, 1,
		1, 8, 9, 5,
		4, 8, 3, 3
	};

	float c[16];
	mat4_mul(c, a, b);
	printf("%f %f %f %f\n", c[0], c[1], c[2], c[3]);
	printf("%f %f %f %f\n", c[4], c[5], c[6], c[7]);
	printf("%f %f %f %f\n", c[8], c[9], c[10], c[11]);
	printf("%f %f %f %f\n", c[12], c[13], c[14], c[15]);

}

//void	rotate_x_axis(); // order?
//void	rotate_y_axis(); // order?
//void	rotate_z_axis(); // order?

//void	scale_mat();
//void	perspective_mat(); // distortion from distance + clipping
//void	orthogonal_mat(); // no distortion from distance + clipping
