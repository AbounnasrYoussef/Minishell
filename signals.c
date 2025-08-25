/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabounna <yabounna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 16:53:44 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/18 16:45:17 by yabounna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios	*ft_get_termios(void)
{
	static struct termios	saved_termios;

	return (&saved_termios);
}

void	save_terminal_settings(void)
{
	tcgetattr(STDIN_FILENO, ft_get_termios());
}

void	restore_terminal_settings(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, ft_get_termios());
}

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_handl_signals == 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_exit_status(1, 1);
	}
	else if (g_handl_signals == 2)
	{
		g_handl_signals = 3;
		write(1, "\n", 1);
		ft_exit_status(1, 1);
		close(0);
	}
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
