/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_here.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:29:58 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/20 00:44:46 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	write_heredoc_line(char *line, t_heredoc_ctx *ctx)
{
	char	*final;

	if (ctx->expand)
	{
		if (heredoc_expansion(line, ctx->env, ctx->garb, &final) == -1)
			return (-1);
	}
	else
		final = ft_strdup(line, ctx->garb);
	write(ctx->fd, final, ft_strlen(final));
	write(ctx->fd, "\n", 1);
	return (0);
}

int	create_heredoc(char *delimiter, int expand, t_list_env *env,
		t_garbage **garb)
{
	int				fd[2];
	char			*line;
	int				saved_stdin;
	t_heredoc_ctx	ctx;

	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	1 && (ctx.expand = expand, ctx.env = env, ctx.garb = garb);
	1 && (ctx.fd = fd[1], saved_stdin = dup(0));
	g_handl_signals = 2;
	while (1)
	{
		line = readline("> ");
		if (g_handl_signals == 3)
			break ;
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		if (write_heredoc_line(line, &ctx) == -1)
			return (free(line), close(fd[0]), close(fd[1]), -1);
		free(line);
	}
	free(line);
	dup2(saved_stdin, 0);
	(close(saved_stdin), close(fd[1]));
	return (fd[0]);
}
