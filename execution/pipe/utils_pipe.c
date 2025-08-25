/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:12:25 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/15 05:52:12 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	ft_count_env(t_list_env *env)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (env != NULL)
	{
		if (env->val != NULL)
		{
			c++;
		}
		env = env->next;
		i++;
	}
	return (c);
}

char	**tab_env(t_list_env *env, t_garbage **garb)
{
	t_list_env	*copy_env;
	char		**tab_env;
	int			i;

	tab_env = NULL;
	tab_env = ft_malloc(garb, sizeof(char *) * (ft_count_env(env) + 1));
	copy_env = env;
	i = 0;
	while (copy_env != NULL)
	{
		if (copy_env->val != NULL)
		{
			tab_env[i] = ft_concat(copy_env->variable, "=", garb);
			tab_env[i] = ft_concat(tab_env[i], copy_env->val, garb);
			i++;
		}
		copy_env = copy_env->next;
	}
	tab_env[i] = NULL;
	return (tab_env);
}

int	is_slash(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '/')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	count_cmd(t_exec *data)
{
	int	i;

	i = 0;
	while (data != NULL)
	{
		data = data->next;
		i++;
	}
	return (i);
}

void	ft_check_signals(int *status)
{
	if (WTERMSIG(*status) == SIGQUIT)
		write(STDOUT_FILENO, "Quit: 3\n\r", 9);
	else if (WTERMSIG(*status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	ft_exit_status(WTERMSIG(*status) + 128, 1);
}
