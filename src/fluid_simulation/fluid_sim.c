/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fluid_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 18:09:22 by jaelee            #+#    #+#             */
/*   Updated: 2019/07/04 19:06:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fluidcube.h"

t_fluidcube *fluidcube_create(float diffusion, float viscosity, float dt)
{
	t_fluidcube		*fluid;

	fluid = (t_fluidcube*)malloc(sizeof(t_fluidcube));
	fluid->density0 = ft_memalloc(N * N * N * sizeof(float));
	fluid->density = ft_memalloc(N * N * N * sizeof(float));
	fluid->vx = ft_memalloc(N * N * N * sizeof(float));
	fluid->vy = ft_memalloc(N * N * N * sizeof(float));
	fluid->vz = ft_memalloc(N * N * N * sizeof(float));
	fluid->vx0 = ft_memalloc(N * N * N * sizeof(float));
	fluid->vy0 = ft_memalloc(N * N * N * sizeof(float));
	fluid->vz0 = ft_memalloc(N * N * N * sizeof(float));
	fluid->dt = dt;
	fluid->size = N;
	fluid->diff = diffusion;
	fluid->visc = viscosity;

	return (fluid);
}

void	fluidcube_add_density(t_fluid *fluid, int x, int y, int z, float density)
{
	fluid->density[IDX(x, y, z)] += density;
}

void	fluidcube_add_velocity(t_fluid *fluid, int x, int y, int z, float velocity[3])
{
	uint32_t	index;

	index = IDX(x, y, z);
	fluid->Vx[index] += velocity[0]
	fluid->Vy[index] += velocity[1];
	fluid->Vz[index] += velocity[2];
}

void	fluidcube_diffuse(int boundary, float *vec, float *vec_prev, float diff_rate, float dt)
{
	diff = dt * diff_rate * (N - 2) * (N - 2);
	linear_solver(boundary, vec, vec_prev, diff, 1 + 6 * diff);
}
