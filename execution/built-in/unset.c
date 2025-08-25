/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:59:18 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/24 15:02:43 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	ft_supp_arg(t_list_env **list_env, char *arg)
{
	t_list_env	*tmp_node;
	t_list_env	*current;

	tmp_node = NULL;
	current = *list_env;
	while (current != NULL)
	{
		if (ft_strcmpp(current->variable, arg) == 0)
		{
			if (tmp_node)
				tmp_node->next = current->next;
			else
				*list_env = current->next;
			break ;
		}
		tmp_node = current;
		current = current->next;
	}
}

void	ft_error_unset(char *arg, int *error)
{
	*error = 1;
	write(2, "unset: `", 8);
	write(2, arg, strlen(arg));
	write(2, ": not a valid identifier\n", 25);
	ft_exit_status(1, 1);
}

void	norm_ft_unset(char **args, int *i, int *j, int *error)
{
	while (args[*i][*j] != '\0')
	{
		if (!(args[*i][*j] == '_'
			|| (args[*i][*j] >= 'a' && args[*i][*j] <= 'z')
			|| (args[*i][*j] >= 'A' && args[*i][*j] <= 'Z')
			|| (args[*i][*j] >= '0' && args[*i][*j] <= '9'))
			|| (args[*i][0] >= '0' && args[*i][0] <= '9'))
		{
			ft_error_unset(args[*i], error);
			break ;
		}
		(*j)++;
	}
}

int	check_error(char **args, int *i, int *error, int flag)
{
	if ((ft_strcmpp(args[*i], "") == 0 || is_espace_tabulion(args[*i]) == 0)
		&& flag == 0)
	{
		ft_error_unset(args[*i], &(*error));
		if (args[*i + 1] != NULL)
		{
			(*i)++;
			return (1);
		}
		else
			return (0);
	}
	if (ft_strcmpp(args[*i], "_") == 0 && flag == 1)
	{
		if (args[*i + 1] != NULL)
		{
			(*i)++;
			return (1);
		}
		else
			return (0);
	}
	return (5);
}

void	ft_unset(t_list_env **list_env, char **args)
{
	int	i;
	int	j;
	int	error;

	i = 1;
	j = 0;
	error = 0;
	while (args[i] != NULL)
	{
		if (check_error(args, &i, &error, 0) == 1)
			continue ;
		else if (check_error(args, &i, &error, 0) == 0)
			break ;
		if (check_error(args, &i, &error, 1) == 1)
			continue ;
		else if (check_error(args, &i, &error, 1) == 0)
			break ;
		norm_ft_unset(args, &i, &j, &error);
		ft_supp_arg(list_env, args[i]);
		j = 0;
		i++;
	}
	if (error == 0)
		ft_exit_status(0, 1);
}
