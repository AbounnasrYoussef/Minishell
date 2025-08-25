/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:02:38 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/24 14:45:17 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

void	error_exit(char *str, int count_cmd, t_garbage **garb)
{
	if (count_cmd == 1)
		write(2, "exit \n", 7);
	write(2, "exit: ", 7);
	write(2, str, ft_strlenn(str));
	write(2, ": numeric argument required\n", 28);
	ft_free_all(garb);
	exit(255);
}

void	error_exit2(int count_cmd)
{
	if (count_cmd == 1)
		printf("exit\n");
	write(2, "exit: too many arguments\n", 25);
	ft_exit_status(1, 1);
}

int	modulo(unsigned long long number)
{
	int	i;
	int	g;

	i = number / 256;
	g = i * 256;
	return (number - g);
}
