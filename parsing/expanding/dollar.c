/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:23:13 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/20 16:35:52 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_value(char *name, t_list_env *env, t_garbage **garb)
{
	while (env)
	{
		if (env->variable && ft_strcmp(env->variable, name) == 0)
			return (ft_strdup(env->val, garb));
		env = env->next;
	}
	return (NULL);
}

static char	*expand_special_vars(char *value, int *i, t_expand_ctx *ctx)
{
	if (!value[*i + 1])
	{
		(*i)++;
		return (ft_strdup("$", ctx->garb));
	}
	if (value[*i + 1] == '$')
	{
		(*i) += 2;
		return (ft_strdup("$$", ctx->garb));
	}
	if (value[*i + 1] == '?')
	{
		(*i) += 2;
		return (ft_itoa(ft_exit_status(0, 0), ctx->garb));
	}
	return (NULL);
}

char	*expand_dollar(char *value, int *i, t_expand_ctx *ctx)
{
	char	*res;
	char	*var_name;
	int		start;

	res = expand_special_vars(value, i, ctx);
	if (res)
		return (res);
	(*i)++;
	if (!is_valid_var_char(value[*i]))
		return (ft_strdup("$", ctx->garb));
	start = *i;
	while (value[*i] && is_valid_var_char(value[*i]))
		(*i)++;
	var_name = ft_substr(value, start, *i - start, ctx->garb);
	return (get_env_value(var_name, ctx->env, ctx->garb));
}
