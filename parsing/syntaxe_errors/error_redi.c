/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:17:40 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/18 18:51:56 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	printf_error(void)
{
	write(2, "minishell: syntax error\n", 25);
	ft_exit_status(258, 1);
	return (-1);
}

static int	check_redir_target(char *str, int *i)
{
	char	quote;

	if (str[*i] == '"' || str[*i] == '\'')
	{
		quote = str[(*i)++];
		while (str[*i] && str[*i] != quote)
			(*i)++;
		if (str[*i] != quote)
			return (printf_error());
		(*i)++;
		return (1);
	}
	if (!str[*i])
		return (printf_error());
	if (str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
		return (printf_error());
	return (1);
}

int	error_redir(char *str, int *i)
{
	if ((str[*i] == '>' && str[*i + 1] == '>')
		|| (str[*i] == '<' && str[*i + 1] == '<'))
		(*i) += 2;
	else
		(*i)++;
	while (str[*i] && skip_space(str[*i]))
		(*i)++;
	return (check_redir_target(str, i));
}
