/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:36:56 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/21 08:18:01 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_red_loop(char *value, t_expand_ctx *ctx,
		t_garbage **garb)
{
	int		i;
	char	*res;
	char	*tmp;

	1 && (i = 0, res = ft_strdup("", garb));
	while (value[i])
	{
		if (value[i] == '\'')
			append_single_quote(value, &i, &res, garb);
		else if (value[i] == '"')
			append_double_quote(value, &i, &res, *ctx);
		else if (value[i] == '$')
		{
			res = ft_strjoin(res, expand_dollar(value, &i, ctx), garb);
			if (check_name(res, garb))
				return (NULL);
		}
		else
		{
			tmp = ft_substr(value, i, 1, garb);
			res = ft_strjoin(res, tmp, garb);
			i++;
		}
	}
	return (res);
}

char	*expand_red(char *value, t_expand_ctx *ctx, t_garbage **garb)
{
	char	*res;

	res = expand_red_loop(value, ctx, garb);
	if (!res)
		return (NULL);
	if (ft_strcmpp(res, "") == 0 && value[0] == '$'
		&& get_env_value(&value[1], ctx->env, garb) == NULL)
		return (NULL);
	return (res);
}

t_token	*check_if_red(t_token *curr, t_garbage **garb,
		t_expand_ctx ctx1)
{
	curr = curr->next;
	if (curr && ft_strchr(curr->value, '$'))
	{
		curr->value = expand_red(curr->value, &ctx1, garb);
		return (curr->next);
	}
	return (curr);
}
