/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:59:42 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/20 00:37:34 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	print_err(void)
{
	write(2, "minishell: syntax error\n", 25);
	ft_exit_status(258, 1);
	return (-1);
}

int	premier_pipe(char *line)
{
	int	i;

	i = 0;
	while (skip_space(line[i]))
		i++;
	if (line[i] == '|')
		return (1);
	return (0);
}

int	error_pipe(char *line, int *i)
{
	int	tmp;

	if (premier_pipe(line) == 1)
		return (print_err());
	(*i)++;
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	if (!line[*i] || line[*i] == '|')
		return (print_err());
	if (line[*i] == '<' || line[*i] == '>')
	{
		tmp = *i;
		if (line[tmp + 1] == line[tmp])
			tmp++;
		tmp++;
		while (line[tmp] && (line[tmp] == ' ' || line[tmp] == '\t'))
			tmp++;
		if (!line[tmp] || line[tmp] == '|' || line[tmp] == '<'
			|| line[tmp] == '>')
			return (print_err());
	}
	return (1);
}
