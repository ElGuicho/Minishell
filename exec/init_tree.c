/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guido <guido@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:05:16 by guido             #+#    #+#             */
/*   Updated: 2025/07/13 17:15:07 by guido            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_leaf(t_node *node)
{
	t_io_node	*io_node;
	int			p[2];
	int			pid;

	if (node->args)
	{
		node->expanded_args = expand(node->args);
	}
}

void	init_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->type == N_PIPE || node->type == N_AND || node->type == N_OR)
	{
		init_tree(node->left);
		if (!g_minishell.heredoc_sigint)
			init_tree(node->right);
	}
	else
		init_leaf(node);
}
