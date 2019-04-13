/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 13:58:39 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/21 13:59:44 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_back(t_list *list)
{
	t_list	*last;

	while (list)
	{
		last = list;
		list = list->next;
	}
	return (last);
}
