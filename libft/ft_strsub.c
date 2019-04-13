/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:09:10 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 16:31:11 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_assert.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	substr = NULL;
	if (s)
	{
		substr = malloc(len + 1);
		MALLOC_ASSERT(substr);
		if (substr)
		{
			ft_memcpy(substr, s + start, len);
			substr[len] = '\0';
		}
	}
	return (substr);
}
