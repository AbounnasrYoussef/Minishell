/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 13:26:51 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/12 16:53:56 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	expand_dollar_in_heredoc(char *line, int *i,
		t_expand_ctx_heredoc *ctx)
{
	int		start;
	char	*varname;
	char	*val;

	(*i)++;
	if (line[*i] == '?')
	{
		*(ctx->tmp) = ft_strjoin(*(ctx->tmp), ft_itoa(ft_exit_status(0, 0),
					ctx->garb), ctx->garb);
		(*i)++;
	}
	else if (is_valid_var_char(line[*i]))
	{
		start = *i;
		while (is_valid_var_char(line[*i]))
			(*i)++;
		varname = ft_substr(line, start, *i - start, ctx->garb);
		val = get_env_value(varname, ctx->env, ctx->garb);
		if (!val)
			val = ft_strdup("", ctx->garb);
		*(ctx->tmp) = ft_strjoin(*(ctx->tmp), val, ctx->garb);
	}
	else
		append_char(ctx->tmp, '$', ctx->garb);
	return (0);
}

int	heredoc_expansion(char *line, t_list_env *env,
		t_garbage **garb, char **res)
{
	int						i;
	char					*tmp;
	t_expand_ctx_heredoc	ctx;

	i = 0;
	tmp = ft_strdup("", garb);
	ctx.env = env;
	ctx.garb = garb;
	ctx.tmp = &tmp;
	while (line[i])
	{
		if (line[i] == '$')
			expand_dollar_in_heredoc(line, &i, &ctx);
		else
			append_char(&tmp, line[i++], garb);
	}
	*res = tmp;
	return (0);
}
