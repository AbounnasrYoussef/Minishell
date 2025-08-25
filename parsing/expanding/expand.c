/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:08:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/20 16:01:38 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_dollar_dquote(char *value, int *i, int exit_code,
		t_expand_ctx *ctx)
{
	char	*result;
	int		start;
	char	raw[3];

	while (value[*i] == '$')
		(*i)++;
	if (value[*i] == '\0')
		return (NULL);
	if (value[*i] == '?')
	{
		result = ft_itoa(exit_code, ctx->garb);
		(*i)++;
		return (result);
	}
	if (ft_isalpha(value[*i]) || value[*i] == '_')
	{
		start = *i;
		while (value[*i] && (ft_isalnum(value[*i]) || value[*i] == '_'))
			(*i)++;
		result = get_env_value(ft_substr(value, start, *i - start, ctx->garb),
				ctx->env, ctx->garb);
		return (result);
	}
	1 && (raw[0] = '$', raw[1] = value[*i], raw[2] = '\0', i++);
	return (ft_strdup(raw, ctx->garb));
}

static void	append_char_dquote(char **res, const char *value,
								int *i, t_garbage **garb)
{
	char	*tmp;

	tmp = ft_strjoin(*res, ft_substr(value, *i, 1, garb), garb);
	(*i)++;
	*res = tmp;
}

char	*expand_token_double_quotes(char *value, int exit_code,
		t_list_env *env, t_garbage **garb)
{
	t_expand_ctx	ctx;
	int				i;
	char			*res;
	char			*exp;

	ctx.env = env;
	ctx.garb = garb;
	ctx.exit_code = exit_code;
	i = 0;
	res = ft_strdup("", garb);
	while (value[i])
	{
		if (value[i] == '$')
		{
			exp = expand_dollar_dquote(value, &i, exit_code, &ctx);
			if (!exp)
				return (value);
			res = ft_strjoin(res, exp, garb);
		}
		else
			append_char_dquote(&res, value, &i, garb);
	}
	return (res);
}

static char	*expand_value(t_token *curr, t_expand_ctx *ctx1,
		t_parsing_context ctx)
{
	if (ctx.quoted_flag == 1)
	{
		return (expand_token_double_quotes(
				curr->value, ctx1->exit_code, ctx1->env, ctx1->garb));
	}
	return (expand_token(
			curr->value, ctx1->exit_code, ctx1->env, ctx1->garb));
}

void	expand_all_tokens(t_token **tokens, int exit_code,
		t_list_env *env, t_parsing_context ctx)
{
	t_token			*curr;
	t_expand_ctx	ctx1;
	t_token			*prev;

	curr = *tokens;
	ctx1.env = env;
	ctx1.exit_code = exit_code;
	ctx1.garb = ctx.garb;
	prev = NULL;
	while (curr)
	{
		if (!should_expand(curr, ctx, prev))
		{
			1 && (prev = curr, curr = curr->next);
			continue ;
		}
		if (curr->type == RDR_IN || curr->type == RDR_OUT)
			curr = check_if_red(curr, ctx1.garb, ctx1);
		else
		{
			curr->value = expand_value(curr, &ctx1, ctx);
			prev = curr;
			curr = update_curr_after_expand(tokens, curr, &ctx1, ctx);
		}
	}
}
