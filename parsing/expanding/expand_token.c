/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:38:12 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/20 15:43:45 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_loop(char *value, t_expand_ctx *ctx, t_garbage **garb)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	res = ft_strdup("", garb);
	while (value[i])
	{
		if (value[i] == '\'')
			append_single_quote(value, &i, &res, garb);
		else if (value[i] == '"')
			append_double_quote(value, &i, &res, *ctx);
		else if (value[i] == '$')
			res = ft_strjoin(res, expand_dollar(value, &i, ctx), garb);
		else
		{
			tmp = ft_substr(value, i, 1, garb);
			res = ft_strjoin(res, tmp, garb);
			i++;
		}
	}
	return (res);
}

char	*expand_token(char *value, int exit_code
		, t_list_env *env, t_garbage **garb)
{
	t_expand_ctx	ctx;

	ctx.exit_code = exit_code;
	ctx.env = env;
	ctx.garb = garb;
	return (expand_loop(value, &ctx, garb));
}
