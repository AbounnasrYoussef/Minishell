/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:41:23 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 16:10:08 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	*ft_memcpyy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (src == dst)
		return (dst);
	s = (char *)src;
	d = (char *)dst;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
