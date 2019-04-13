/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:16:27 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 16:31:09 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_assert.h"
#include <stdlib.h>

static size_t	count_words(char const *s, char c)
{
	size_t index;
	size_t words;

	index = 0;
	words = 0;
	if (!s)
		return (0);
	while (s[index])
	{
		while (s[index] && s[index] == c)
			index++;
		if (s[index])
			words++;
		while (s[index] && s[index] != c)
			index++;
	}
	return (words);
}

static size_t	word_length(char const *s, char c)
{
	size_t length;

	length = 0;
	while (s[length] && s[length] != c)
		length++;
	return (length);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;
	size_t	index;
	size_t	word_index;

	array = (char**)malloc(sizeof(char*) * (count_words(s, c) + 1));
	MALLOC_ASSERT(array);
	if (array)
	{
		index = 0;
		word_index = 0;
		while (s && s[index])
		{
			while (s[index] && s[index] == c)
				index++;
			if (s[index])
			{
				array[word_index] = ft_strnew(word_length(&s[index], c));
				ft_strncpy(array[word_index++], &s[index],
						word_length(&s[index], c));
			}
			while (s[index] && s[index] != c)
				index++;
		}
		array[word_index] = 0;
	}
	return (array);
}
