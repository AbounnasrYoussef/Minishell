/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 09:58:57 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/24 14:46:56 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "../../minishell.h"
# include <stdlib.h>
# include <string.h>

typedef struct s_garbage	t_garbage;

t_garbage	*ft_last(t_garbage *head);
void		*ft_malloc(t_garbage **garb, size_t size);
void		ft_free_all(t_garbage **garb);

#endif
