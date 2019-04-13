/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:48:24 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/26 13:09:28 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_pop(t_list **begin)
{
	t_list	*ret;

	if (!begin || !(*begin))
		return (NULL);
	ret = *begin;
	*begin = (*begin)->next;
	if (*begin)
		(*begin)->prev = ret->prev;
	if (ret->prev)
		ret->prev->next = (*begin);
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}
