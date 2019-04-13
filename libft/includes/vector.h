/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 02:49:41 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/11 02:55:04 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VECTOR_H
# define _VECTOR_H
# include "libft.h"

typedef struct	s_vector
{
	void	**data;
	size_t	reserved;
	size_t	length;
}				t_vector;

void	vector_init(t_vector *vec);
int		vector_length(t_vector *vec);
int		vector_add(t_vector *vec, void *data);
int		vector_remove(t_vector *vec, size_t index);
void	*vector_get(t_vector *vec, size_t index);
int		vector_free(t_vector *vec);

#endif
