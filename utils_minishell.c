/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:36:44 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/24 16:04:38 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution/execution.h"

void	norm_read_loop(t_exec **data, t_read_loop	inf_read)
{
	expand_all_tokens(&inf_read.token, inf_read.last_exit_code,
		inf_read.env, inf_read.ctx);
	*data = parse_tokens_to_exec_list(inf_read.token, &inf_read.garb);
}

int	check_exist_path(t_list_env *env)
{
	t_list_env	*copy_env;

	copy_env = env;
	while (copy_env)
	{
		if (ft_strcmpp(copy_env->variable, "PATH") == 0)
		{
			return (0);
		}
		copy_env = copy_env->next;
	}
	return (1);
}

void	add_path(t_read_loop *inf_read)
{
	if (check_exist_path((*inf_read).env) == 1)
	{
		lst_add_back(&(*inf_read).env, ft_lstnew("PATH", PATHD,
				&(*inf_read).garb));
		(*inf_read).flag_path = 1;
	}
}

void	ft_readline(t_read_loop *inf_read)
{
	g_handl_signals = 0;
	save_terminal_settings();
	setup_signals();
	(*inf_read).line = readline("minishell$ ");
}
