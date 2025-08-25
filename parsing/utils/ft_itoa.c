/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:13:21 by yabounna          #+#    #+#             */
/*   Updated: 2025/07/31 14:23:57 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_char(char *s, unsigned int number, long int len)
{
	while (number > 0)
	{
		s[len--] = '0' + (number % 10);
		number = number / 10;
	}
	return (s);
}

static long int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n, t_garbage **garb)
{
	char				*s;
	long int			len;
	unsigned int		number;
	int					sign;

	if (n == 0)
		return (ft_strdup("0", garb));
	sign = 1;
	len = ft_len(n);
	s = (char *)ft_malloc(garb, sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	s[len--] = '\0';
	if (n < 0)
	{
		sign = -1;
		number = (unsigned int)(-n);
		s[0] = '-';
	}
	else
		number = (unsigned int)n;
	s = ft_char(s, number, len);
	return (s);
}
