/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:37:21 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/20 09:05:25 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*handle_expanded_tokens(t_token **tokens, t_token *curr,
		t_expand_ctx *ctx1, t_parsing_context ctx)
{
	t_token	*new_tokens;

	(void) ctx;
	if (ft_strcmpp(curr->value, "") != 0)
	{
		if (!if_only_space(curr->value))
		{
			new_tokens = split_tokens_by_space(curr->value,
					ctx1->garb, curr->type);
			replace_token(tokens, curr, new_tokens);
		}
	}
	else
		curr->value = NULL;
	return (curr->next);
}

t_token	*get_last_token(t_token *tokens)
{
	while (tokens && tokens->next)
		tokens = tokens->next;
	return (tokens);
}

t_token	*split_tokens_by_space(char *str, t_garbage **garb, t_type_token type)
{
	t_token	*head;
	t_token	*new_token;
	char	**words;
	int		i;

	i = 0;
	head = NULL;
	if (!str)
		return (NULL);
	words = ft_split(str, ' ', garb);
	if (!words)
		return (NULL);
	while (words[i])
	{
		if (words[i][0] != '\0')
		{
			new_token = new_token_0(words[i], type, garb);
			new_token->quoted = 0;
			add_token_back(&head, new_token);
		}
		i++;
	}
	return (head);
}

static void	link_new_list(t_token **head, t_token *prev,
							t_token *old, t_token *new_list)
{
	t_token	*last;

	if (new_list)
	{
		last = new_list;
		while (last->next)
			last = last->next;
		last->next = old->next;
	}
	else if (prev)
		prev->next = old->next;
	else
		*head = old->next;
}

void	replace_token(t_token **head, t_token *old, t_token *new_list)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = *head;
	while (curr && curr != old)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr)
		return ;
	if (!prev)
		*head = new_list;
	else
		prev->next = new_list;
	link_new_list(head, prev, old, new_list);
}
