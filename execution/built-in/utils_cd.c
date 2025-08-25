/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uilis_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:53:25 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/07 16:20:50 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	check_home(t_list_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmpp(env->variable, "HOME") == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
