/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 23:17:33 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/10 01:07:53 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	trait_cmd1(char *str)
{
	if (str == NULL)
		return (1);
	if (ft_strcmpp(str, "echo") == 0)
		return (0);
	return (1);
}

int	trait_cmd2(char *str)
{
	int	i;

	i = 0;
	if (ft_strcmpp(str, "-n") == 0)
		return (0);
	else if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

void	if_cmd2(int i, char **str)
{
	while (str[i] != NULL && trait_cmd2(str[i]) == 0)
		i++;
	while (str[i] != NULL)
	{
		ft_put_string(str[i]);
		if (str[i + 1] != NULL)
			ft_put_string(" ");
		i++;
	}
}

void	if_n_cmd2(int i, char **str)
{
	while (str[i] != NULL)
	{
		ft_put_string(str[i]);
		if (str[i + 1] != NULL)
			ft_put_string(" ");
		i++;
	}
	ft_put_string("\n");
}

void	ft_echo(char **str)
{
	int	i;
	int	argc;

	i = 0;
	argc = ft_strlen_argc(str);
	if (argc > 1)
	{
		if (trait_cmd1(str[0]) == 0)
		{
			if (trait_cmd2(str[1]) == 0)
			{
				i = 2;
				if_cmd2(i, str);
			}
			else if (trait_cmd2(str[1]) == 1)
			{
				i = 1;
				if_n_cmd2(i, str);
			}
		}
	}
	else if (argc == 1 && trait_cmd1(str[0]) == 0)
		write(1, "\n", 1);
	ft_exit_status(0, 1);
}
