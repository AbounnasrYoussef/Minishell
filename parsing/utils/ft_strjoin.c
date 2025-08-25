/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:53:55 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/02 10:37:53 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*check(char const *s1, char const *s2, t_garbage **garb)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2, garb));
	if (!s2)
		return (ft_strdup(s1, garb));
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2, t_garbage **garb)
{
	char	*dup;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (check(s1, s2, garb));
	dup = (char *)ft_malloc(garb, sizeof(char) * (ft_strlen(s1)
				+ ft_strlen(s2) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		dup[j++] = s1[i++];
	i = 0;
	while (s2[i])
		dup[j++] = s2[i++];
	dup[j] = '\0';
	return (dup);
}
