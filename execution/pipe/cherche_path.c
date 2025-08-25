/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cherche_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 22:06:32 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/24 14:45:24 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	norm_cherch_path2(char **paths, char *cmd, t_garbage **garb, int i)
{
	if (access(paths[i], X_OK) != 0 && errno == 13)
	{
		write(2, cmd, ft_strlenn(cmd));
		write(2, ": Permission denied\n", 20);
		(ft_free_all(garb), exit(126));
	}
	else
		error_cherch_path(cmd, garb);
}

char	*cherch_path2(t_exec *data, t_list_env **env, t_inf_cher_path inf_path
	, t_garbage **garb)
{
	char	**paths;
	char	*path_cmd;
	int		i;

	i = 0;
	(void)env;
	path_cmd = NULL;
	paths = ft_splitt(inf_path.path, ':', garb);
	while (paths && paths[i] && (paths[i] != NULL))
	{
		paths[i] = ft_concat(paths[i], "/", garb);
		paths[i] = ft_concat(paths[i], data->cmd[0], garb);
		if (access(paths[i], X_OK) == 0)
		{
			path_cmd = paths[i];
			break ;
		}
		i++;
	}
	if (path_cmd == NULL && is_built_in(data->cmd[0]) == -1)
		norm_cherch_path2(paths, data->cmd[0], garb, i);
	return (path_cmd);
}

char	*cherch_path1(t_exec *data, t_list_env **env, int count_cmd
		, t_garbage **garb)
{
	t_inf_cher_path	inf_path;

	inf_path.path = NULL;
	inf_path.c_cmd = count_cmd;
	while (*env != NULL)
	{
		if (ft_strcmpp((*env)->variable, "PATH") == 0)
		{
			inf_path.path = (*env)->val;
			break ;
		}
		(*env) = (*env)->next;
	}
	if (inf_path.path == NULL)
	{
		if (access(data->cmd[0], X_OK) != 0)
		{
			write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
			write(2, ": No such file or directory\n", 28);
			(ft_free_all(garb), exit(127));
		}
	}
	return (cherch_path2(data, env, inf_path, garb));
}

int	chech_path(t_list_env **env)
{
	t_list_env	*copy_env;

	copy_env = *env;
	while (copy_env)
	{
		if (ft_strcmpp(copy_env->variable, "PATH") == 0
			&& copy_env->val != NULL)
		{
			if (ft_strcmpp(copy_env->val, "") == 0)
				return (1);
			return (0);
		}
		copy_env = copy_env->next;
	}
	return (1);
}

char	*cherch_path(t_list_env **env, t_exec *data, int count_cmd
		, t_garbage **garb)
{
	if (is_espace_tabulion(data->cmd[0]) == 0)
		error_cherch_path(data->cmd[0], garb);
	if (!data->cmd[0] || !data->cmd[0][0])
		return (NULL);
	if (data->cmd[0][0] == '/' || data->cmd[0][0] == '.'
		|| chech_path(env) == 1)
	{
		if (access(data->cmd[0], X_OK) == 0)
			return (data->cmd[0]);
		return (NULL);
	}
	return (cherch_path1(data, env, count_cmd, garb));
}
