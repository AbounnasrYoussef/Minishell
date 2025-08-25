/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 00:10:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/20 11:21:46 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	exp_el_help(t_list_env **env, char *args
		, t_export indx, t_garbage **garb)
{
	int	k;

	k = 0;
	norm_exp_el_h(args, &indx, garb);
	if (verif_exist(env, indx.arg_ex[0]) == 0 && args[indx.i - 1] != '=')
		lst_add_back(env, ft_lstnew(indx.arg_ex[0], NULL, garb));
	else if (verif_exist(env, indx.arg_ex[0]) == 1 && args[indx.i - 1] != '=')
		;
	else
	{
		while (args[indx.i] != '\0')
		{
			indx.arg_ex[1][k] = args[indx.i];
			k++;
			indx.i++;
		}
		indx.arg_ex[1][k] = '\0';
		if (verif_exist(env, indx.arg_ex[0]) == 0)
			lst_add_back(env, ft_lstnew(indx.arg_ex[0], indx.arg_ex[1], garb));
		else
		{
			if (indx.arg_ex[1] != NULL)
				chng_el(env, indx, garb);
		}
	}
}

void	export_el(t_list_env **env, char *args, t_export indx,
		t_read_loop *inf_read)
{
	indx.i = 0;
	indx.j = 0;
	indx.c = 0;
	indx.arg_ex = ft_malloc(&(*inf_read).garb, 2 * sizeof(char *));
	while (args[indx.j] != '\0' && args[indx.j] != '=' && args[indx.j] != '+')
		indx.j++;
	indx.arg_ex[0] = ft_malloc(&(*inf_read).garb, indx.j + 1);
	while (indx.i < indx.j)
	{
		indx.arg_ex[0][indx.i] = args[indx.i];
		indx.i++;
	}
	indx.arg_ex[0][indx.i] = '\0';
	change_flag_path(&(*inf_read), indx);
	if (args[indx.i] == '+' && args[indx.i + 1] == '=')
	{
		indx.c = 1;
		indx.i += 2;
	}
	else if (args[indx.i] == '=')
		indx.i++;
	if (args[indx.i] == '\0')
		indx.arg_ex[1] = NULL;
	indx.j = 0;
	exp_el_help(env, args, indx, &(*inf_read).garb);
}

void	check_args(t_list_env **env, t_export ix, char **args,
		t_read_loop *inf_read)
{
	while (args[ix.i] != NULL)
	{
		if (ft_strcmpp(args[ix.i], "") == 0)
		{
			error_export(args, ix.i, &(ix.error));
			if (args[ix.i + 1] != NULL)
			{
				ix.i++;
				continue ;
			}
		}
		else
		{
			if (norm_check_arg2(args, &ix) == 0)
				break ;
			else if (norm_check_arg2(args, &ix) == 1)
				continue ;
			export_el(env, args[ix.i], ix, &(*inf_read));
			ix.j = 1;
		}
		ix.i++;
	}
	if (ix.error == 0)
		ft_exit_status(0, 1);
}

t_list_env	*ex_sort(t_list_env *list_env, char *tmp)
{
	t_list_env	*list1;
	t_list_env	*debut;

	list1 = list_env;
	debut = list1;
	while (list_env != NULL)
	{
		list1 = debut;
		while (list1 != NULL)
		{
			if (ft_strcmpp(list1->variable, (list_env->variable)) > 0)
			{
				tmp = list1->variable;
				list1->variable = list_env->variable;
				list_env->variable = tmp;
				tmp = list1->val;
				list1->val = list_env->val;
				list_env->val = tmp;
				list1 = debut;
			}
			list1 = list1->next;
		}
		list_env = list_env->next;
	}
	return (debut);
}

void	ft_export(t_list_env *list_env, char **args, t_read_loop *inf_read)
{
	int			c;
	t_export	index;

	c = ft_strlen_argc(args);
	index.i = 1;
	index.j = 1;
	index.c = 0;
	if (c == 1)
	{
		ft_print_env_ex(ex_sort(list_env, NULL), &(*inf_read));
		ft_exit_status(0, 1);
	}
	else
	{
		check_args(&list_env, index, args, &(*inf_read));
	}
}
