/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:35:39 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/16 17:39:09 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "math.h"

void	mat4_translation(float *mat, float x_axis, float y_axis, float z_axis)
{
	mat4_identity(mat);
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
	mat4_identity(mat);
	rot[0 * 4 + 0] = cos(y_axis);
	rot[0 * 4 + 2] = -sin(y_axis);
	rot[2 * 4 + 0] = sin(y_axis);
	rot[2 * 4 + 2] = cos(y_axis);
	mat4_multiply(tmp, rot, mat);
	mat4_identity(rot);
	rot[1 * 4 + 1] = cos(x_axis);
	rot[1 * 4 + 2] = sin(x_axis);
	rot[2 * 4 + 1] = -sin(x_axis);
	rot[2 * 4 + 2] = cos(x_axis);
	mat4_multiply(mat, rot, tmp);

	// mat4_identity(tmp);
	// mat4_identity(rot);
	// rot[0 * 4 + 0] = cos(y_axis);
	// rot[0 * 4 + 1] = -sin(y_axis);
	// rot[1 * 4 + 0] = sin(y_axis);
	// rot[1 * 4 + 1] = cos(y_axis);
	// mat4_multiply(mat, rot, tmp);
}

void	mat4_scaling(float *mat, float scale)
{
	mat4_identity(mat);
	mat[0] *= scale;
	mat[5] *= scale;
	mat[10] *= scale;
}

// int main()
// {
// 	float a[16] = {
// 		1, 3, 5, 7,
// 		2, 7, 9, 1,
// 		1, 8, 9, 5,
// 		4, 8, 3, 3
// 	};
// 	float b[16] = {
// 		1, 3, 5, 7,
// 		2, 7, 9, 1,
// 		1, 8, 9, 5,
// 		4, 8, 3, 3
// 	};

// 	float c[16];
// 	mat4_mul(c, a, b);
// 	printf("%f %f %f %f\n", c[0], c[1], c[2], c[3]);
// 	printf("%f %f %f %f\n", c[4], c[5], c[6], c[7]);
// 	printf("%f %f %f %f\n", c[8], c[9], c[10], c[11]);
// 	printf("%f %f %f %f\n", c[12], c[13], c[14], c[15]);
// }
