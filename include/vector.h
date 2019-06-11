/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 18:07:33 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/11 17:13:02 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

void	vec3_normalize(float *vec);
void	vec3_add(float *dst, float *vec1, float *vec2);
void	vec3_sub(float *dst, float *vec1, float *vec2);
void	vec3_scale(float *vec, float scale);
void	vec3_scale_dst(float *dst, float *vec, float scale);
void	vec3_cross(float *dst, float *vec1, float *vec2);
float	vec3_dot(float *vec1, float *vec2);
float	vec3_size(float *vec);

#endif
