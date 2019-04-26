/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:15:09 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 16:30:46 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_assert.h"
#include <stdlib.h>

static char		*append(char *str, char chr)
{
	char	*ret;
	size_t	index;

	index = 0;
	while (str[index])
		index++;
	ret = malloc(index + 2);
	MALLOC_ASSERT(ret);
	if (!ret)
		return (NULL);
	index = 0;
	while (str[index])
		ret[index] = str[index];
	ret[index++] = chr;
	ret[index] = '\0';
	free(str);
	return (ret);
}

static int		find_largest_divisor(int number, int base_size)
{
	int	divisor;

	divisor = base_size;
	while (ABS(number / divisor) >= base_size)
		divisor *= base_size;
	return (divisor);
}

char			*ft_itoa_base(int number, const char *base)
{
	size_t	base_size;
	int		divisor;
	char	started;
	char	*str;

	base_size = ft_strlen(base);
	str = ft_strnew(0);
	if (number < 0)
		str = append(str, '-');
	divisor = find_largest_divisor(number, base_size);
	started = 0;
	while (divisor >= 1)
	{
		if (started || divisor == 1 || ABS(number / divisor) > 0)
		{
			started = 1;
			str = append(str, ABS(number / divisor) + '0');
			number = number - (number / divisor) * divisor;
		}
		divisor /= base_size;
	}
	return (str);
}
