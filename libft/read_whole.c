/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_whole.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:33:14 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/19 16:03:59 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int		read_whole(int fd, char *buffer, size_t size)
{
	size_t	read_bytes;
	ssize_t	ret_value;

	read_bytes = 0;
	while (((ret_value = read(fd, buffer + read_bytes, size - read_bytes)) >= 0)
		&& (read_bytes + ret_value) < size)
		read_bytes += ret_value;
	if (ret_value <= 0)
		return (ret_value);
	return (read_bytes + ret_value);
}
