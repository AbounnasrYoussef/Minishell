/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 08:22:31 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/20 15:43:57 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_expanded_dollar(const char *val, int *i, t_expand_ctx *ctx)
{
	return (expand_dollar((char *)val, i, ctx));
}

void	append_double_quote(const char *val, int *i
		, char **res, t_expand_ctx ctx)
{
	char			*part;
	char			*tmp;
	t_expand_ctx	subctx;

	subctx.exit_code = ctx.exit_code;
	subctx.env = ctx.env;
	subctx.garb = ctx.garb;
	(*i)++;
	part = ft_strdup("", ctx.garb);
	while (val[*i] && val[*i] != '"')
	{
		if (val[*i] == '$')
			part = ft_strjoin(part,
					get_expanded_dollar(val, i, &subctx),
					ctx.garb);
		else
		{
			tmp = ft_substr(val, *i, 1, ctx.garb);
			part = ft_strjoin(part, tmp, ctx.garb);
			(*i)++;
		}
	}
	*res = ft_strjoin(*res, part, ctx.garb);
	if (val[*i] == '"')
		(*i)++;
}
