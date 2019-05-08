/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 01:05:53 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/08 14:13:18 by jaelee           ###   ########.fr       */
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

void	mat4_translation(float *mat, float x_axis, float y_axis, float z_axis)
{
	identity_mat4(mat);
	mat[0 + 3 * 1] += x_axis;
	mat[1 + 3 * 2] += y_axis;
	mat[2 + 3 * 3] += z_axis;
}

void	mat4_rotation(float *mat, float x_axis, float y_axis)
{
	float rot[16];
	float tmp[16];

	mat4_identity(tmp);
	mat4_identity(rot);
	rot[0 * 4 + 0] = cos(y_axis);
	rot[0 * 4 + 2] = -sin(y_axis);
	rot[2 * 4 + 0] = sin(y_axis);
	rot[2 * 4 + 2] = cos(x_axis);
	mat4_multiply(tmp, rot, mat);
	mat4_identity(rot);
	rot[1 * 4 + 1] = cos(x_axis);
	rot[1 * 4 + 2] = sin(x_axis);
	rot[2 * 4 + 1] = -sin(x_axis);
	rot[2 * 4 + 2] = cos(x_axis);
	mat4_multiply(mat, rot, tmp);
}

void	scaling_mat4(float *mat, float scale)
{
	mat4_identity(mat);
	mat[0] *= scale;
	mat[5] *= scale;
	mat[10] *= scale;
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
