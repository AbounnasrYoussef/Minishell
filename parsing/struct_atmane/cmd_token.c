/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 09:26:22 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/14 20:09:37 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**extract_cmd_from_tokens(t_token *segment, t_garbage **garb)
{
	char	**cmd;
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = segment;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->value
			&& (tmp->value[0] != '\0' || tmp->quoted))
			count++;
		tmp = tmp->next;
	}
	cmd = ft_malloc(garb, sizeof(char *) * (count + 1));
	count = 0;
	tmp = segment;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->value
			&& (tmp->value[0] != '\0' || tmp->quoted))
			cmd[count++] = tmp->value;
		tmp = tmp->next;
	}
	cmd[count] = NULL;
	return (cmd);
}
