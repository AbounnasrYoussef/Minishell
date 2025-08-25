/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 10:44:05 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/19 18:06:35 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exec	*init_new_cmd(t_garbage **garb, int count)
{
	t_exec	*new_cmd;

	new_cmd = ft_malloc(garb, sizeof(t_exec));
	new_cmd->cmd = ft_malloc(garb, (count + 1) * sizeof(char *));
	new_cmd->files = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	free_exec_list(t_exec *exec_list)
{
	t_exec	*tmp;
	int		i;

	while (exec_list)
	{
		tmp = exec_list->next;
		if (exec_list->cmd)
		{
			i = 0;
			while (exec_list->cmd[i])
			{
				free(exec_list->cmd[i]);
				i++;
			}
			free(exec_list->cmd);
		}
		free(exec_list);
		exec_list = tmp;
	}
}
