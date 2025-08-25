/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:22:24 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/12 19:48:03 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_single_operator(const char *line, int *i
		, t_token **tokens, t_garbage **garb)
{
	char	op[2];

	op[0] = line[*i];
	op[1] = '\0';
	add_token(tokens, new_token_0(ft_strdup(op, garb),
			get_token_type(op), garb));
	(*i)++;
}

void	handel_double_operator(const char *line, int *i
		, t_token **tokens, t_garbage **garb)
{
	char	op[3];

	op[0] = line[*i];
	op[1] = line[*i + 1];
	op[2] = '\0';
	add_token(tokens, new_token_0(ft_strdup(op, garb),
			get_token_type(op), garb));
	*i += 2;
}

void	handel_quote(const char *line, int *i
		, t_token **token, t_garbage **garb)
{
	char	quote;
	int		start;
	char	*quoted;

	start = *i;
	quote = line[(*i)++];
	while (line[*i] && line[*i] != quote)
	{
		(*i)++;
	}
	(*i)++;
	quoted = ft_substr(line, start, *i - start, garb);
	add_token(token, new_token_0(quoted, WORD, garb));
}
