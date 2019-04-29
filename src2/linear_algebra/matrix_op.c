/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 01:05:53 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/29 22:50:32 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

Matrix multiplymat4(const Matrix* m1, const Matrix* m2) {
	Matrix out = IDENTITY_MATRIX;
	unsigned int row, column, row_offset;

	for (row = 0, row_offset = row * 4; row < 4; ++row, row_offset = row * 4)
		for (column = 0; column < 4; ++column)
			out.m[row_offset + column] =
				(m1->m[row_offset + 0] * m2->m[column + 0]) +
				(m1->m[row_offset + 1] * m2->m[column + 4]) +
				(m1->m[row_offset + 2] * m2->m[column + 8]) +
				(m1->m[row_offset + 3] * m2->m[column + 12]);

	return out;
}

void	mat4_mul();
void	mat4_vec4_mul();
void	mat4_translate();
void	vec4_dot();

void	rotate_x_axis(); // order?
void	rotate_y_axis(); // order?
void	rotate_z_axis(); // order?

void	scale_mat();
void	perspective_mat(); // distortion from distance + clipping
void	orthogonal_mat(); // no distortion from distance + clipping
