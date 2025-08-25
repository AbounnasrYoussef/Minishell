/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 22:49:31 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/24 15:55:18 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

char	*help_pwd(t_list_env *env, t_garbage **garb)
{
	char	*buffer;
	char	*tmp;

	buffer = NULL;
	tmp = getcwd(NULL, 0);
	if (tmp != NULL)
	{
		buffer = ft_strdup(tmp, garb);
		free(tmp);
	}
	else
	{
		while (env != NULL)
		{
			if (ft_strcmpp(env->variable, "PWD") == 0
				|| ft_strcmpp(env->variable, "") == 0
				|| ft_strcmpp(env->variable, "OLD_PWD") == 0)
			{
				buffer = env->val;
				break ;
			}
			env = env->next;
		}
	}
	return (buffer);
}

char	*ft_pwd(t_list_env *env, t_garbage **garb)
{
	char	*buffer;

	buffer = help_pwd(env, garb);
	if (buffer == NULL)
		buffer = "ahaha";
	ft_exit_status(0, 1);
	return (buffer);
}
