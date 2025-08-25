/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:01:21 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/11 01:05:28 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	verif_exist(t_list_env **list_env, char *arg)
{
	t_list_env	*l_env;

	l_env = *list_env;
	while (l_env != NULL)
	{
		if (ft_strcmpp((l_env)->variable, arg) == 0)
		{
			return (1);
			break ;
		}
		(l_env) = (l_env)->next;
	}
	return (0);
}

void	chng_el(t_list_env **env, t_export indx, t_garbage **garb)
{
	t_list_env	*l_env;

	l_env = *env;
	while (l_env != NULL)
	{
		if (ft_strcmpp((l_env)->variable, indx.arg_ex[0]) == 0)
		{
			if (indx.c == 1)
			{
				(l_env)->val = ft_concat((l_env)->val, indx.arg_ex[1], garb);
			}
			else
				(l_env)->val = indx.arg_ex[1];
		}
		(l_env) = (l_env)->next;
	}
}

void	error_export(char **args, int i, int *error)
{
	*error = 1;
	write(2, "export: `", 9);
	write(2, args[i], ft_strlenn(args[i]));
	write(2, "' not a valid identifier\n", 25);
	ft_exit_status(1, 1);
}

int	ft_isalnumm(int c)
{
	unsigned char	s;

	s = (unsigned char)c;
	if ((s >= '0' && s <= '9') || (s >= 'a' && s <= 'z')
		|| (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isalphaa(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
