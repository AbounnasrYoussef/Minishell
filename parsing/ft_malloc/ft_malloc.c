/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:58:59 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/24 14:47:48 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_garbage	*ft_last(t_garbage *head)
{
	t_garbage	*last;

	last = head;
	while (last->next)
		last = last->next;
	return (last);
}

void	*ft_malloc(t_garbage **garb, size_t size)
{
	void		*ptr;
	t_garbage	*new;

	ptr = malloc(size);
	if (!ptr)
		return (ft_free_all(garb), exit(EXIT_FAILURE), NULL);
	new = malloc(sizeof(t_garbage));
	if (!new)
	{
		ft_free_all(garb);
		free(ptr);
		exit(EXIT_FAILURE);
		return (NULL);
	}
	new->ptr = ptr ;
	if (*garb == NULL)
		*garb = new;
	else
		ft_last(*garb)->next = new;
	new->next = NULL;
	return (ptr);
}

void	ft_free_all(t_garbage **garb)
{
	t_garbage	*current;
	t_garbage	*tmp;

	current = *garb;
	while (current)
	{
		free(current->ptr);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*garb = NULL;
}
