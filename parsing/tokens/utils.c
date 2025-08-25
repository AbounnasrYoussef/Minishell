/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:29:03 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/15 06:56:39 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_token(t_token **list, t_token *new_tok)
{
	t_token	*tmp;

	if (!*list)
		*list = new_tok;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_tok;
	}
}

t_token	*new_token_0(char *value, t_type_token type, t_garbage **garb)
{
	t_token	*tok;

	tok = ft_malloc(garb, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = ft_strdup(value, garb);
	tok->type = type;
	tok->join = 0;
	tok->quoted = 0;
	tok->double_quote = 0;
	tok->next = NULL;
	return (tok);
}
