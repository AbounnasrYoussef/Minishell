/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:13:22 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/20 11:05:32 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_print_env_ex(t_list_env *env, t_read_loop *inf_read)
{
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "PATH") == 0
			&& (*inf_read).flag_path == 1)
		{
			env = env->next;
			continue ;
		}
		if (ft_strcmp(env->variable, "") != 0)
		{
			if (ft_strcmpp(env->variable, "_") != 0)
			{
				if (env->val != NULL)
					printf("declare -x %s=\"%s\"\n", env->variable, env->val);
				else
					printf("declare -x %s\n", env->variable);
			}
		}
		env = env->next;
	}
}

void	ft_print_env(t_list_env *env, t_read_loop *inf_read)
{
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "PATH") == 0
			&& (*inf_read).flag_path == 1)
		{
			env = env->next;
			continue ;
		}
		if (ft_strcmp(env->variable, "") != 0)
		{
			if (env->val != NULL && ft_strcmpp(env->val, "") != 0)
			{
				printf("%s=%s\n", env->variable, env->val);
			}
		}
		env = env->next;
	}
}

int	norm_help_built(t_list_env **env, char **cmd)
{
	ft_unset(env, cmd);
	if (check_exist_pwd(*env) == 1)
		ft_change_oldpwd(env);
	return (0);
}

int	is_built_in(char *str)
{
	if (ft_strcmpp(str, "export") == 0)
		return (0);
	else if (ft_strcmpp(str, "cd") == 0)
		return (0);
	else if (ft_strcmpp(str, "echo") == 0)
		return (0);
	else if (ft_strcmpp(str, "env") == 0)
		return (0);
	else if (ft_strcmpp(str, "exit") == 0)
		return (0);
	else if (ft_strcmpp(str, "pwd") == 0)
		return (0);
	else if (ft_strcmpp(str, "unset") == 0)
		return (0);
	return (-1);
}
