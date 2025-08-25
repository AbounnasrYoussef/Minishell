/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:33:56 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 14:22:55 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_substr(char const *s, unsigned int start,
		size_t len, t_garbage **garb)
{
	char			*sub;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup("", garb));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = (char *)ft_malloc(garb, (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
