/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:09:22 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/24 17:06:46 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../minishell.h"

void	ft_error_pipe(t_exec *data, t_garbage **garb)
{
	if (data->cmd[0] && data->cmd[0][0] == '.' && data->cmd[0][1] == '\0')
	{
		write(2, ".: filename argument required\n", 30);
		write(2, ".: usage: . filename [arguments]\n", 33);
		(ft_free_all(garb), exit(2));
	}
}

void	ft_error_pipe2(t_exec *data, t_info_pipe inf_pip, t_garbage **garb)
{
	if (ft_strcmpp(data->cmd[0], "..") == 0)
		error_cherch_path(data->cmd[0], garb);
	if (S_ISDIR((inf_pip.info).st_mode) && is_slash(data->cmd[0]) == 0)
	{
		if (ft_strcmpp(data->cmd[0], "..") != 0)
		{
			write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
			write(2, ": is a directory \n", 18);
			(ft_free_all(garb), exit(126));
		}
	}
	else if (errno == 20)
	{
		write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
		write(2, ": Not a directory\n", 18);
		(ft_free_all(garb), exit(126));
	}
	else if (!S_ISREG((inf_pip.info).st_mode) && is_slash(data->cmd[0]) == 0)
	{
		write(2, data->cmd[0], ft_strlenn(data->cmd[0]));
		write(2, ": No such file or directory\n", 28);
		(ft_free_all(garb), exit(127));
	}
}

void	ft_error_fork(void)
{
	int	i;

	i = 3;
	perror("fork");
	while (i++ < 1024)
		close(i);
	ft_exit_status(1, 1);
}

void	ft_wait_child(t_info_pipe *inf_pip)
{
	while (inf_pip->j < inf_pip->i)
	{
		wait(NULL);
		(inf_pip->j)++;
	}
}

void	norm_ft_exec_child(char *cmd, t_garbage **garb)
{
	if (!cmd)
		exit(1);
	if (errno == 13)
	{
		write(2, cmd, ft_strlenn(cmd));
		write(2, ": Permission denied\n", 20);
		(ft_free_all(garb), exit(126));
	}
	else
	{
		write(2, cmd, ft_strlenn(cmd));
		write(2, ": No such file or directory\n", 28);
		(ft_free_all(garb), exit(127));
	}
}
