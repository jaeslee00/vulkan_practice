/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 00:32:22 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 16:28:45 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "libft.h"

void	list_add(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		new->next = (*alst);
		if (*alst)
			(*alst)->prev = new;
		*alst = new;
	}
}
