/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_reserve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 14:47:25 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 16:31:51 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "ft_assert.h"

void	fast_copy(void *dst, const void *src, size_t size)
{
	size_t index;

	index = 0;
	while (size >= 8 && index < size - 8)
	{
		((uint64_t*)dst)[index / 8] = ((uint64_t*)src)[index / 8];
		index += 8;
	}
	while (size >= 4 && index < size - 4)
	{
		((uint32_t*)dst)[index / 4] = ((uint32_t*)src)[index / 4];
		index += 4;
	}
	while (size >= 2 && index < size - 2)
	{
		((uint16_t*)dst)[index / 2] = ((uint16_t*)src)[index / 2];
		index += 2;
	}
	ft_memcpy(dst + index, src + index, size - index);
}

void	array_reserve(t_array *array, size_t size)
{
	if (array->reserved >= size)
		return ;
	array->ptr = realloc(array->ptr, size);
	MALLOC_ASSERT(array->ptr);
	array->reserved = size;
}
