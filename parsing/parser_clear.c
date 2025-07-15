/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:50:51 by guido             #+#    #+#             */
/*   Updated: 2025/07/15 23:24:07 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clear_io_list(t_io_node **io_list)
{
	t_io_node	*current;
	t_io_node	*next;

	current = *io_list;
	if (!current)
		return ;
	while (current)
	{
		free (current->value);
		ft_free_char2(current->expanded_value);
		next = current->next;
		free(current);
		current = next;
	}
	*io_list = NULL;
}

void	clear_cmd_node(t_node *node)
{
	if (!node)
		return ;
	clear_io_list(&(node->io_list));
	free(node->args);
	ft_free_char2(node->expanded_args);
}

void	recursive_clear_ast(t_node *node)
{
	if (!node)
		return ;
	if (node->type == N_CMD)
		clear_cmd_node(node);
	else
	{
		if (node->left)
			recursive_clear_ast(node->left);
		if (node->right)
			recursive_clear_ast(node->right);
	}
	free(node);
}

void	clear_ast(t_node **ast)
{
	recursive_clear_ast(*ast);
	*ast = NULL;
	clear_token_list(&g_minishell.tokens);
}
