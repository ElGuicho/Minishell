/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guido <guido@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:21:14 by guido             #+#    #+#             */
/*   Updated: 2025/07/12 19:40:15 by guido            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redir(t_token_type type)
{
	if (type == T_LESS || type == T_GREAT
		|| type == T_DLESS || type == T_DGREAT)
		return (true);
	return (false);
}

int	prec(t_token_type type)
{
	if (type == T_OR || type == T_AND)
		return (0);
	return (1);
}

void	curr_token_prec(void)
{
	return (prec(g_minishell.curr_token->type));
}

void	get_next_token(void)
{
	g_minishell.curr_token = g_minishell.curr_token->next;
}

bool	curr_token_is_bin(void)
{
	t_token_type	type;

	if (!g_minishell.curr_token)
		return (false);
	type = g_minishell.curr_token->type;
	if (type == T_PIPE || type == T_AND || type == T_OR)
		return (true);
	return (false);
}
