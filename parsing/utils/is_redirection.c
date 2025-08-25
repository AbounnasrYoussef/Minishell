/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 09:06:54 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/20 11:02:49 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirection(t_type_token type)
{
	return (type == RDR_IN || type == RDR_OUT
		|| type == APPEND || type == HERE_DOC);
}
