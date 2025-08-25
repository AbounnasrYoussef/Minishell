/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:36:12 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/19 22:49:06 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_input(int *fd, char *file_name)
{
	*fd = open(file_name, O_RDONLY);
	dup2(*fd, STDIN_FILENO);
	close(*fd);
}

void	ft_output(int *fd, char *file_name, struct stat info)
{
	*fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd == -1 && S_ISDIR(info.st_mode))
	{
		write(2, file_name, ft_strlenn(file_name));
		write(2, ": is a directory \n", 18);
		ft_exit_status(126, 1);
	}
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
}

void	ft_output_append(int *fd, char *file_name)
{
	*fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	dup2(*fd, STDOUT_FILENO);
	close(*fd);
}

void	ft_herdoc(int *fd)
{
	dup2(*fd, STDIN_FILENO);
	close(*fd);
}
