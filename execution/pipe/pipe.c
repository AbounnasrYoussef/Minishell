/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:36:08 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/24 17:29:31 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"
#include "../../minishell.h"

void	ft_one_cmd(t_exec *data, t_list_env **env, int count_cmd
		, t_read_loop *inf_read)
{
	int	original_fd_in;
	int	original_fd_out;

	if (data->files == NULL)
		ft_built_in(data, env, count_cmd, &(*inf_read));
	else
	{
		original_fd_in = dup(STDIN_FILENO);
		original_fd_out = dup(STDOUT_FILENO);
		ft_redirection(data, &(*inf_read).garb);
		ft_built_in(data, env, count_cmd, &(*inf_read));
		dup2(original_fd_in, STDIN_FILENO);
		dup2(original_fd_out, STDOUT_FILENO);
		close(original_fd_in);
		close(original_fd_out);
	}
}

void	ft_exec_child(t_exec *data, t_list_env **env, t_info_pipe inf_pip
		, t_read_loop *inf_read)
{
	if (data->files != NULL)
		ft_redirection(data, &(*inf_read).garb);
	stat(data->cmd[0], &(inf_pip.info));
	ft_error_pipe(data, &(*inf_read).garb);
	ft_error_pipe2(data, inf_pip, &(*inf_read).garb);
	inf_pip.in_bultin = ft_built_in(data, env, inf_pip.count_cmd, &(*inf_read));
	if (inf_pip.in_bultin == -1)
	{
		inf_pip.path_cmd = cherch_path(env, data, inf_pip.count_cmd,
				&(*inf_read).garb);
		if (inf_pip.path_cmd)
		{
			data->cmd[0] = inf_pip.path_cmd;
			execve(inf_pip.path_cmd, data->cmd, inf_pip.tab_envv);
			(ft_free_all(&(*inf_read).garb), exit(ft_exit_status(0, 0)));
		}
		if (access(data->cmd[0], X_OK) == -1)
			norm_ft_exec_child(data->cmd[0], &(*inf_read).garb);
	}
	else
		exit(ft_exit_status(0, 0));
}

void	ft_child(t_exec *data, t_list_env **env, t_info_pipe *inf_pip
		, t_read_loop *inf_read)
{
	if (inf_pip->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (inf_pip->in_fd != STDIN_FILENO)
		{
			dup2(inf_pip->in_fd, STDIN_FILENO);
			close(inf_pip->in_fd);
		}
		if (data->next != NULL)
		{
			dup2(inf_pip->fd[1], STDOUT_FILENO);
			1 && (close(inf_pip->fd[0]), close(inf_pip->fd[1]));
		}
		ft_exec_child(data, env, *inf_pip, &(*inf_read));
	}
	else
	{
		if (data->next != NULL)
			close(inf_pip->fd[1]);
		if (inf_pip->in_fd != STDIN_FILENO)
			close(inf_pip->in_fd);
		if (data->next != NULL)
			inf_pip->in_fd = inf_pip->fd[0];
	}
}

void	ft_plusieur_cmd(t_exec *data, t_list_env **env, t_info_pipe *inf_pip
		, t_read_loop *inf_read)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (data != NULL)
	{
		if (data->next != NULL)
		{
			if (pipe(inf_pip->fd) == -1)
			{
				perror("pipe");
				(ft_free_all(&(*inf_read).garb), exit(1));
			}
		}
		inf_pip->pid = fork();
		if (inf_pip->pid == -1)
		{
			ft_exit_status(1, 1);
			return (ft_error_fork());
		}
		else
			ft_child(data, env, inf_pip, &(*inf_read));
		data = data->next;
		(inf_pip->i)++;
	}
}

void	ft_pipe(t_exec *data, t_list_env **env, t_read_loop *inf_read)
{
	t_info_pipe	inf_pip;
	int			status;

	inf_pip.i = 0;
	inf_pip.j = 0;
	status = 0;
	inf_pip.in_fd = STDIN_FILENO;
	inf_pip.tab_envv = tab_env(*env, &(*inf_read).garb);
	inf_pip.count_cmd = count_cmd(data);
	if (count_cmd(data) == 1 && ft_strlen_argc(data->cmd) == 1
		&& ft_strcmpp(data->cmd[0], "export") != 0
		&& is_built_in(data->cmd[0]) == 0)
		return (ft_one_cmd(data, env, count_cmd(data), &(*inf_read)));
	else if (count_cmd(data) == 1 && ft_strlen_argc(data->cmd) != 1
		&& is_built_in(data->cmd[0]) == 0)
		return (ft_one_cmd(data, env, count_cmd(data), &(*inf_read)));
	else
		ft_plusieur_cmd(data, env, &inf_pip, &(*inf_read));
	waitpid(inf_pip.pid, &status, 0);
	ft_status(data, &status);
	ft_wait_child(&inf_pip);
	(restore_terminal_settings(), setup_signals());
}
