/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:50:46 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 16:36:44 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ASSERT_H
# define _ASSERT_H

# define ASSERT(cond, message) ft_assert(cond, message, __FILE__, __LINE__)
# define MALLOC_ASSERT(ptr) ASSERT(!(!(ptr)), "Call to malloc returned NULL.")
# ifdef _DEBUG
#  define ASSERT_DBG(cond, message) ASSERT(cond, message)
# else
#  define ASSERT_DBG(cond, message)
#endif

void	ft_assert(char cond, const char *message, const char *file, int line);

#endif
