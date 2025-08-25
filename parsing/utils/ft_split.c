/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 10:09:11 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/23 21:23:44 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	count_word(const char *s, char c)
{
	size_t	len;
	size_t	count;

	len = 0;
	count = 0;
	while (s[len])
	{
		while (s[len] == c)
			len++;
		if (s[len])
			count++;
		while (s[len] && s[len] != c)
			len++;
	}
	return (count);
}

static int	count_len_word(const char *s, char c, size_t *j, size_t *skip)
{
	size_t	length;

	length = 0;
	while (s[*j] == c)
		(*j)++;
	*skip = *j;
	while (s[*j] && s[*j] != c)
	{
		length++;
		(*j)++;
	}
	return (length);
}

char	**ft_split(const char *s, char c, t_garbage **garb)
{
	size_t	skip;
	size_t	i;
	size_t	index;
	size_t	word_len;
	char	**result;

	if (!s)
		return (NULL);
	result = ft_malloc(garb, sizeof(char *) * (count_word(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	index = 0;
	while (index < count_word(s, c))
	{
		word_len = count_len_word(s, c, &i, &skip);
		result[index] = ft_malloc(garb, sizeof(char) * (word_len + 1));
		ft_memcpy(result[index], s + skip, word_len);
		result[index][word_len] = '\0';
		index++;
	}
	result[index] = NULL;
	return (result);
}
