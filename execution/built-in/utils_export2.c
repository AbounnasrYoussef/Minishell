/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 00:44:30 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/20 11:22:08 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	norm_check_arg(char **args, t_export *ix)
{
	if (!(args[(*ix).i][0] == '_' || ft_isalphaa(args[(*ix).i][0])))
	{
		1 && (error_export(args, (*ix).i, &((*ix).error)), (*ix).c = 1);
		if (args[(*ix).i + 1] != NULL)
			return ((*ix).i++, 1);
		else
			return (0);
	}
	while (args[(*ix).i][(*ix).j] != '\0' && args[(*ix).i][(*ix).j] != '='
		&& args[(*ix).i][(*ix).j] != '+')
	{
		if (!(args[(*ix).i][(*ix).j] == '_' || args[(*ix).i][(*ix).j] == '='
			|| ft_isalnumm(args[(*ix).i][(*ix).j])))
		{
			1 && (error_export(args, (*ix).i, &((*ix).error)), (*ix).c = 1);
			if (args[(*ix).i + 1] != NULL)
				return ((*ix).i++, 1);
			else
				return (0);
		}
		(*ix).j++;
	}
	return (5);
}

int	norm_check_arg2(char **args, t_export *ix)
{
	if (norm_check_arg(args, ix) == 0)
		return (0);
	else if (norm_check_arg(args, ix) == 1)
		return (1);
	else if (args[(*ix).i][(*ix).j] == '+')
	{
		if (args[(*ix).i][((*ix).j) + 1] != '=')
		{
			1 && (error_export(args, (*ix).i, &((*ix).error)), (*ix).c = 1);
			if (args[(*ix).i + 1] != NULL)
			{
				(*ix).i++;
				return (1);
			}
			else
				return (0);
		}
		(*ix).j++;
	}
	return (5);
}

void	norm_exp_el_h(char *args, t_export *indx, t_garbage **garb)
{
	while (args[(*indx).i] != '\0')
	{
		(*indx).i++;
		(*indx).j++;
	}
	(*indx).i = (*indx).i - (*indx).j;
	(*indx).arg_ex[1] = ft_malloc(garb, ((*indx).j + 1));
}

void	change_flag_path(t_read_loop *inf_read, t_export indx)
{
	if (ft_strcmpp(indx.arg_ex[0], "PATH") == 0)
		(*inf_read).flag_path = 0;
}
