/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:00:14 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/20 00:43:43 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	error_quote(char *caracter, int *i)
{
	char	quote;

	quote = 0;
	if (caracter[*i] == '\'' || caracter[*i] == '\"')
	{
		quote = caracter[(*i)++];
		while (caracter[*i] && caracter[*i] != quote)
			(*i)++;
		if (caracter[*i] == quote)
		{
			quote = 0;
			(*i)++;
		}
		if (quote != 0)
		{
			write(2, "minishell: syntax error\n", 25);
			ft_exit_status(258, 1);
			return (-1);
		}
	}
	return (1);
}
