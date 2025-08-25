/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 09:21:08 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/21 10:13:27 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	append_char(char **tmp, char c, t_garbage **garb)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	*tmp = ft_strjoin(*tmp, str, garb);
}

int	count_nbr_herdoc(t_file *file)
{
	int	i;

	i = 0;
	while (file != NULL)
	{
		if (file->type == HERE_DOC)
			i++;
		file = file->next;
	}
	return (i);
}

static void	print_e(t_file *file)
{
	if (count_nbr_herdoc(file) > 15)
	{
		printf("maximum here-document count exceeded\n");
		exit(2);
	}
}

void	process_heredocs(char *line, t_exec *exec,
		t_list_env *env, t_garbage **garb)
{
	t_file	*file;
	int		expand;

	expand = 1;
	while (exec)
	{
		file = exec->files;
		while (file)
		{
			if (ft_strchr(line, '\'') || ft_strchr(line, '"'))
				expand = 0;
			if (file->type == HERE_DOC)
			{
				print_e(file);
				file->fd = create_heredoc(file->file_name, expand, env, garb);
			}
			if (g_handl_signals == 3)
				break ;
			file = file->next;
		}
		if (g_handl_signals == 3)
			break ;
		exec = exec->next;
	}
}
