/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:33:27 by arahhab           #+#    #+#             */
/*   Updated: 2025/08/16 16:00:16 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

t_list_env	*ft_lstnew(void *variable, void *val, t_garbage **garb)
{
	t_list_env	*list1;

	(void)garb;
	list1 = ft_malloc(garb, sizeof(t_list_env));
	if (list1 == NULL)
	{
		return (NULL);
	}
	list1->variable = variable;
	list1->val = val;
	list1->next = NULL;
	return (list1);
}

void	lst_add_back(t_list_env **lst, t_list_env *new)
{
	t_list_env	*temp;

	if (new == NULL || lst == NULL)
	{
		return ;
	}
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
}

t_list_env	*ft_envvv(char **str, t_garbage **garb)
{
	t_list_env	*copy_env;
	t_list_env	*debut_env;
	char		**splitt;
	int			i;
	int			j;

	i = 0;
	j = 0;
	copy_env = NULL;
	while (str[i] != NULL )
	{
		splitt = ft_splitt(str[i], '=', garb);
		if (splitt[1] != NULL)
		{
			lst_add_back(&copy_env, ft_lstnew(splitt[0], splitt[1], garb));
			if (ft_strcmpp(splitt[0], "PWD") == 0)
				lst_add_back(&copy_env, ft_lstnew("", splitt[1], garb));
		}
		else
			lst_add_back(&copy_env, ft_lstnew(splitt[0], NULL, garb));
		if (i == 0)
			debut_env = copy_env;
		i++;
	}
	return (debut_env);
}
