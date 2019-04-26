/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_shrink.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 15:07:13 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/31 16:24:59 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "ft_assert.h"

void	array_shrink(t_array *array)
{
	size_t	malloc_size;

	malloc_size = array->elem_size * array->length;
	ASSERT(array->reserved <= malloc_size, "Reserved memory less than necessary to hold array.");
	array->ptr = realloc(array->ptr, malloc_size);
	MALLOC_ASSERT(array->ptr);
	array->reserved = malloc_size;
}
