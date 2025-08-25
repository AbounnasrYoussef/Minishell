/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:57:55 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/20 12:41:33 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*update_curr_after_expand(t_token **tokens,
		t_token *curr, t_expand_ctx *ctx1, t_parsing_context ctx)
{
	if (ctx.quoted_flag == 0)
	{
		return (handle_expanded_tokens(tokens, curr, ctx1, ctx));
	}
	return (curr->next);
}

void	append_single_quote(const char *val, int *i
		, char **res, t_garbage **garb)
{
	int		start;
	char	*tmp;

	start = ++(*i);
	while (val[*i] && val[*i] != '\'')
		(*i)++;
	tmp = ft_substr(val, start, *i - start, garb);
	*res = ft_strjoin(*res, tmp, garb);
	if (val[*i] == '\'')
		(*i)++;
}
