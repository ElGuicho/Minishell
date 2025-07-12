/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guido <guido@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:12:16 by guido             #+#    #+#             */
/*   Updated: 2025/07/12 20:49:12 by guido            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*combine_nodes(t_token_type op_type, t_node *left, t_node *right)
{
	t_node	*node;

	if (g_minishell.parse_err.type)
		return (NULL);
	node = new_node(get_node_type(op_type));
	if (!node)
		return (set_parse_err(E_MEM), NULL);
	node->left = left;
	node->right = right;
	return (node);
}

t_node	op_mng(int min_prec)
{
	t_node			*left;
	t_node			*right;
	int				n_prec;
	t_token_type	op_type;

	if (g_minishell.parse_err.type || g_minishell.curr_token == NULL)
		return (NULL);
	left = term();
	if (!left)
		return (NULL);
	while (curr_token_is_bin() && curr_token_prec() >= min_prec)
	{
		op_type = g_minishell.curr_token->type;
		get_next_token();
		if (!g_minishell.curr_token)
			return (set_parse_err(E_SYNTAX), left);
		n_prec = prec(op_type) + 1;
		right = op_mng(n_prec);
		if (!right)
			return (left);
		left = combine_nodes(op_type, left, right);
		if (!left)
			return (clear_ast(&left), clear_ast(&right), NULL);
	}
	return (left);
}

t_node	*term(void)
{
	t_node	*node;

	if (g_minishell.parse_err.type)
		return (NULL);
	if (curr_token_is_bin() || g_minishell.curr_token->type == T_C_PARENT)
		return (set_parse_err(E_SYNTAX), NULL);
	else if (g_minishell.curr_token->type == T_O_PARENT)
	{
		get_next_token();
		node = op_mng(0);
		if (!node)
			return (set_parse_err(E_MEM), NULL);
		if (!g_minishell.curr_token
			|| g_minishell.curr_token->type != T_C_PARENT)
			return (set_parse_err(E_SYNTAX), NULL);
		get_next_token();
		return (node);
	}
	else
		return (get_simple_cmd());
}

t_node	*ft_parse(void)
{
	t_node	*ast;

	g.minishell.curr_token = g.minishell.tokens;
	ast = op_mng(0);
	if (g_minishell.curr_token)
		return (set_parse_err(E_SYNTAX), ast);
	return (ast);
}
