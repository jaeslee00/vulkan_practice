/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 01:06:41 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/12 00:05:42 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MATRIX_H
# define _MATRIX_H

# include "libft.h"

void	mat4_multiply(float *dst, float *mat1, float *mat2);
void	mat4_identity(float *mat);

void	mat4_scaling(float *mat, float scale);
void	mat4_rotation(float *mat, float x_axis, float y_axis);
void	mat4_translation(float *mat, float x_axis, float y_axis, float z_axis);
#endif
