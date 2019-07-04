/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fluidcube.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 17:32:25 by jaelee            #+#    #+#             */
/*   Updated: 2019/07/04 17:55:45 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLUIDCUBE_H
# define FLUIDCUBE_H
#include <math.h>
#include <stdint.h>
#include "libft.h"
# define N 512
# define ITER 4
# define IDX(x, y, z) ((x) + (y) * N + (z) * N * N)

typedef struct	s_fluidcube
{
	uint32_t size;
	float dt;
	float diff;
	float visc;
	float *density;
	float *density;
	float *vx;
	float *vy;
	float *vz;
	float *vx0;
	float *vy0;
	float *vz0;
}				t_fluidcube;

#endif
