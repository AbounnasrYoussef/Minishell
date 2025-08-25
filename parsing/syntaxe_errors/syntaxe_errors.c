/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 08:11:03 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/20 00:43:21 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	syntaxe_errors(char *args)
{
	int	i;

	i = 0;
	while (args[i] != '\0')
	{
		if (args[i] == '\'' || args[i] == '\"')
		{
			if (error_quote(args, &i) == -1)
				return (0);
		}
		else if (args[i] == '|')
		{
			if (error_pipe(args, &i) == -1)
				return (0);
		}
		else if (args[i] == '>' || args[i] == '<')
		{
			if (error_redir(args, &i) == -1)
				return (0);
		}
		else
			i++;
	}
	return (1);
}
