/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 14:29:07 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/10 14:56:23 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "math.h"

void	vec3_add(float *dst, float *vec1, float *vec2)
{
	dst[0] = vec1[0] + vec2[0];
	dst[1] = vec1[1] + vec2[1];
	dst[2] = vec1[2] + vec2[2];
}

void	vec3_sub(float *dst, float *vec1, float *vec2)
{
	dst[0] = vec1[0] - vec2[0];
	dst[1] = vec1[1] - vec2[1];
	dst[2] = vec1[2] - vec2[2];
}

float	vec3_dot(float *vec1, float *vec2)
{
	float	ret;

	ret = (vec1[0] * vec2[0]) +
			(vec1[1] * vec2[1]) +
				(vec1[2] * vec2[2]);

	return (ret);
}

void	vec3_cross(float *dst, float *vec1, float *vec2)
{
	dst[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	dst[1] = vec1[0] * vec2[2] - vec1[2] * vec2[0];
	dst[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

void	vec3_normalize(float *vec)
{
	float	normalize_factor;

	normalize_factor =
	1 / (sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2])));
	vec[0] = normalize_factor * vec[0];
	vec[1] = normalize_factor * vec[1];
	vec[2] = normalize_factor * vec[2];
}

/*TODO if possible SIMD */
