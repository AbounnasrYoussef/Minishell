/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:19:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/20 13:04:02 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_file	*create_file_node(t_token *token, t_garbage **garb)
{
	t_file	*f;

	f = ft_malloc(garb, sizeof(t_file));
	f->type = token->type;
	if (token->next->value == NULL)
		f->file_name = NULL;
	else
		f->file_name = ft_strdup(token->next->value, garb);
	f->next = NULL;
	return (f);
}

static void	fill_cmd_or_file(t_fill_ctx *ctx)
{
	if (is_redirection((*(ctx->tokens))->type) && (*(ctx->tokens))->next)
	{
		**(ctx->current) = create_file_node(*(ctx->tokens), ctx->garb);
		*(ctx->current) = &(**(ctx->current))->next;
		*(ctx->tokens) = (*(ctx->tokens))->next;
	}
	else
	{
		ctx->new_cmd->cmd[ctx->i] = (*(ctx->tokens))->value;
		(ctx->i)++;
	}
}

static void	parse_single_command(t_token **tokens, t_exec *new_cmd,
		t_garbage **garb)
{
	t_file		**current;
	t_fill_ctx	ctx;

	current = &(new_cmd->files);
	ctx.new_cmd = new_cmd;
	ctx.current = &current;
	ctx.tokens = tokens;
	ctx.i = 0;
	ctx.garb = garb;
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->value)
			fill_cmd_or_file(&ctx);
		*tokens = (*tokens)->next;
	}
	new_cmd->cmd[ctx.i] = NULL;
	if (*tokens && (*tokens)->type == PIPE)
		*tokens = (*tokens)->next;
}

static int	count_argument(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens->type != PIPE)
	{
		tokens = tokens->next;
		i++;
	}
	return (i);
}

t_exec	*parse_tokens_to_exec_list(t_token *tokens, t_garbage **garb)
{
	t_exec	*head;
	t_exec	*cmd;
	t_exec	*new_cmd;
	int		count;

	head = NULL;
	cmd = NULL;
	count = 0;
	while (tokens)
	{
		count = count_argument(tokens);
		new_cmd = init_new_cmd(garb, count);
		if (!head)
			head = new_cmd;
		else
			cmd->next = new_cmd;
		cmd = new_cmd;
		parse_single_command(&tokens, new_cmd, garb);
	}
	return (head);
}
