/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:53:52 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/23 21:23:19 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

static size_t	count_word(char const *s, char c)
{
	size_t	len;
	size_t	count;

	len = 0;
	count = 0;
	while (s[len])
	{
		while (s[len] == c)
			len++;
		while (s[len])
		{
			if (s[len] == c || s[len + 1] == '\0')
			{
				count++;
				break ;
			}
			len++;
		}
		if (s[len] == '\0')
			break ;
		len++;
	}
	return (count);
}

static int	count_len_word(char const *s, char c, size_t *j, size_t *skip)
{
	size_t	longueur;

	longueur = 0;
	while (s[*j] == c)
		(*j)++;
	*skip = *j;
	while (s[*j])
	{
		if (s[*j] != c)
			longueur++;
		else
			break ;
		(*j)++;
	}
	return (longueur);
}

static char	**alloc(char const *s, char c, t_garbage **garb)
{
	char	**sp;

	(void)garb;
	if (!s)
		return (NULL);
	sp = ft_malloc(garb, sizeof(char *) * (count_word(s, c) + 1));
	if (!sp)
		return (NULL);
	return (sp);
}

char	**ft_splitt(char const *s, char c, t_garbage **garb)
{
	size_t	skip;
	size_t	i;
	size_t	index;
	size_t	siz;
	char	**alloce_array;

	(void)garb;
	skip = 0;
	i = 0;
	index = 0;
	siz = 0;
	alloce_array = alloc(s, c, garb);
	if (!alloce_array)
		return (NULL);
	while (index < count_word(s, c))
	{
		siz = count_len_word(s, c, &i, &skip);
		alloce_array[index] = (char *)ft_malloc(garb, sizeof(char) * (siz + 1));
		ft_memcpyy(alloce_array[index], s + skip, siz);
		alloce_array[index][siz] = '\0';
		index++;
	}
	return (alloce_array[index] = NULL, alloce_array);
}
