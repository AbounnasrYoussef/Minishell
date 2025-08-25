/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:41:33 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/19 15:02:25 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	should_expand(t_token *curr, t_parsing_context ctx, t_token *prev)
{
	if (!curr->value[0])
		return (0);
	if (prev && prev->type == HERE_DOC)
		return (0);
	if (ctx.quoted_flag == 2)
		return (0);
	if (ctx.quoted_flag == 1)
		return (1);
	if (curr->value[0] == '$' && curr->value[1] == '"')
		return (0);
	return (1);
}

void	add_token_back(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!head || !new_token)
		return ;
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

int	ft_exit_status(int status, int flag)
{
	static int	exit_status;

	if (flag)
		exit_status = status;
	return (exit_status);
}

int	is_valid_var_char(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || (c == '_'));
}

char	*ft_strtrim_custom(char *str, t_garbage **garb, int quoted)
{
	if (quoted)
		return (str);
	return (ft_strtrim(str, " \t", garb));
}
