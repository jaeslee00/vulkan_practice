/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:35:20 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/15 12:13:29 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"
#include "open-simplex-noise.h"

float	noise_filter(struct osn_context *ctx, float *pos, t_noise_attr *attr)
{
	double	v;
	float	noise_value;
	float	freq;
	float	amplitude;
	int		layer_index;

	freq = attr->freq;
	amplitude = attr->amplitude;
	noise_value = 0.0f;
	layer_index = 0;
	while (layer_index < attr->layers)
	{
		v = open_simplex_noise3(ctx, pos[0] * freq, pos[1] * freq, pos[2] * freq);
		noise_value += (1.f + v) * 0.5f * amplitude;
		freq *= attr->freq_delta;
		amplitude *= attr->amp_delta;
		layer_index++;
	}
	/* squeezing noise_value between [a, b] */
	float a = 0.65f;
	float b = 1.3f;
	noise_value = (b - a) * (noise_value - 0.574338) / (1.476342 - 0.574338) + a;

	return (noise_value);
}
