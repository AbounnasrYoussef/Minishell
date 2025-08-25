/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cherch_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:37:51 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/24 14:45:53 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*ft_concat(char *str, char *str2, t_garbage **garb)
{
	int		i;
	int		j;
	char	*new_str;

	(void)garb;
	if (str == NULL)
		return (str2);
	if (str2 == NULL)
		return (str);
	new_str = ft_malloc(garb, (ft_strlenn(str) + ft_strlenn(str2) + 1));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	while (str2[j] != '\0')
	{
		new_str[i] = str2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	is_espace_tabulion(char *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return (1);
	while (cmd[i] != '\0')
	{
		if (cmd[i] != ' ' && cmd[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

void	error_cherch_path(char *cmd, t_garbage **garb)
{
	write(2, cmd, ft_strlenn(cmd));
	write(2, ": command not found\n", 20);
	ft_free_all(garb);
	exit(127);
}
