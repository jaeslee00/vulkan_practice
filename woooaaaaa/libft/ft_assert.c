/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:20:56 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 16:20:45 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"
#include "libft.h"

void	ft_assert(char cond, const char *message, const char *file, int line)
{
	if (!cond)
	{
		ft_putstr_fd("Assert failed at ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(", line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(message, 2);
		exit(0);
	}
}
