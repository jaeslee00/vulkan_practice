/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:40:07 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 16:31:01 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_assert.h"
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char *str;

	str = (char*)malloc(size + 1);
	MALLOC_ASSERT(str);
	if (str)
		ft_memset(str, 0, size + 1);
	return (str);
}
