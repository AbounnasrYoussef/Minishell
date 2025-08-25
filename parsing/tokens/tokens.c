/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arahhab <arahhab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 12:44:25 by yabounna          #+#    #+#             */
/*   Updated: 2025/08/15 06:56:39 by arahhab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_type_token	get_token_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	if (!ft_strcmp(str, "<"))
		return (RDR_IN);
	if (!ft_strcmp(str, "<<"))
		return (HERE_DOC);
	if (!ft_strcmp(str, ">"))
		return (RDR_OUT);
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	return (WORD);
}

t_token	*tokens(const char *line, t_garbage **garb, t_parsing_context	*ctx)
{
	t_token				*tokens;
	int					i;

	tokens = NULL;
	i = 0;
	(*ctx).line = line;
	(*ctx).index = &i;
	(*ctx).garb = garb;
	while (line[i] != '\0')
	{
		space_skip(line, &i);
		if (!line[i])
			break ;
		if ((line[i] == '<' || line[i] == '>') && line[i + 1] == line[i])
			handel_double_operator(line, &i, &tokens, garb);
		else if (is_operator(line[i]))
			handle_single_operator(line, &i, &tokens, garb);
		else
			handle_word(ctx, &tokens);
	}
	return (tokens);
}
