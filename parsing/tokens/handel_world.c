/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:38:19 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/19 09:55:16 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*new_token(char *value, t_type_token type, int i, t_garbage **garb)
{
	t_token	*tok;

	tok = ft_malloc(garb, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = ft_strdup(value, garb);
	tok->type = type;
	tok->join = 1;
	tok->quoted = i;
	tok->double_quote = 0;
	tok->next = NULL;
	return (tok);
}

static void	handle_quoted_part(t_parsing_context *ctx
		, char **res, int *quoted_flag)
{
	char	quote;
	int		start;
	char	*substr;

	quote = ctx->line[*ctx->index];
	(*ctx->index)++;
	start = *ctx->index;
	while (ctx->line[*ctx->index] && ctx->line[*ctx->index] != quote)
		(*ctx->index)++;
	substr = ft_substr(ctx->line, start, *ctx->index - start, ctx->garb);
	*res = ft_strjoin(*res, substr, ctx->garb);
	if (quote == '\'')
		*quoted_flag = 2;
	else if (quote == '"')
		*quoted_flag = 1;
	if (ctx->line[*ctx->index] == quote)
		(*ctx->index)++;
}

static char	*handle_non_quoted_part(t_parsing_context *ctx)
{
	int		start;
	char	*word;
	char	*res;

	res = NULL;
	start = *ctx->index;
	while (ctx->line[*ctx->index] && !skip_space(ctx->line[*ctx->index])
		&& !is_operator(ctx->line[*ctx->index])
		&& ctx->line[*ctx->index] != '\''
		&& ctx->line[*ctx->index] != '"')
		(*ctx->index)++;
	word = ft_substr(ctx->line, start, *ctx->index - start, ctx->garb);
	res = ft_strjoin(res, word, ctx->garb);
	return (res);
}

void	handle_word(t_parsing_context *ctx, t_token **tokens)
{
	char	*res;

	ctx->quoted_flag = 0;
	res = NULL;
	res = ft_strdup("", ctx->garb);
	while (ctx->line[*ctx->index] && !skip_space(ctx->line[*ctx->index])
		&& !is_operator(ctx->line[*ctx->index]))
	{
		if (ctx->line[*ctx->index] == '\'' || ctx->line[*ctx->index] == '\"')
			handle_quoted_part(ctx, &res, &ctx->quoted_flag);
		else
			res = handle_non_quoted_part(ctx);
	}
	if (res)
		add_token(tokens, new_token(res, WORD, ctx->quoted_flag, ctx->garb));
}
