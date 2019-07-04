/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlap_test1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 10:50:05 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/26 14:23:34 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "overlap_test.h"

int	aabb_test(float v0, float v1, float v2, float half_size)
{
	float	min;
	float	max;

	min = v0;
	max = v0;
	if (v1 < min)
		min = v1;
	if (v1 > max)
		max = v1;
	if (v2 < min)
		min = v2;
	if (v2 > max)
		max = v2;
	if (min > half_size || max < -half_size)
		return (0);
	return (1);
}
