/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:05:16 by guido             #+#    #+#             */
/*   Updated: 2025/07/14 22:56:31 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	ft_clean_ms();
	exit(SIGINT);
}

void	ft_heredoc(t_io_node *io, int p[2])
{
	char	*line;
	char	*quotes;

	signal(SIGINT, heredoc_sigint_handler);
	quotes = io->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_delimiter(io->value, line))
			break ;
		if (!*quotes)
			heredoc_expander(line, p[1]);
		else
		{
			ft_putstr_fd(line, p[1]);
			ft_putstr_fd("\n", p[1]);
		}
	}
	clean_ms();
	exit(0);
}

static bool	leave_leaf(int p[2], int *pid)
{
	waitpid(*pid, pid, 0);
	signal(SIGQUIT, sigquit_handler);
	g_minishell.signint_child = false;
	close(p[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (true);
	return (false);
}

void	init_leaf(t_node *node)
{
	t_io_node	*io_node;
	int			p[2];
	int			pid;

	if (node->args)
		node->expanded_args = expand(node->args);
	io_node = node->io_list;
	while (io_node)
	{
		if (io_node->type == IO_HEREDOC)
		{
			pipe(p);
			g_minishell.signint_child = true;
			pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (!pid)
				ft_heredoc(io_node, p);
			if (leave_leaf(p, &pid))
				return ;
			io_node->here_doc = p[0];
		}
		else
			io_node->expanded_value = expand(io_node->value);
		io_node = io_node->next;
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
