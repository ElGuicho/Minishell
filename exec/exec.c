/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:07:59 by gmunoz            #+#    #+#             */
/*   Updated: 2025/07/15 22:58:16 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	exec_pipe_child(t_node *node, int pfds[2], t_ast_direction drctn)
{
	int	status;

	if (drctn == TD_LEFT)
	{
		close(pfds[0]);
		dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
	}
	else if (drctn == TD_RIGHT)
	{
		close(pfds[1]);
		dup2(pfds[0], STDIN_FILENO);
		close(pfds[0]);
	}
	status = exec_node(node, true);
	(clean_ms(), exit(status));
}

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static	int	exec_pipeline(t_node *tree)
{
	int	status;
	int	pfds[2];
	int	pid_l;
	int	pid_r;

	g_minishell.signint_child = true;
	pipe(pfds);
	pid_l = fork();
	if (!pid_l)
		exec_pipe_child(tree->left, pfds, TD_LEFT);
	else
	{
		pid_r = fork();
		if (!pid_r)
			exec_pipe_child(tree->right, pfds, TD_RIGHT);
		else
		{
			(close(pfds[0]), close(pfds[1]),
				waitpid(pid_l, &status, 0), waitpid(pid_r, &status, 0));
			g_minishell.signint_child = false;
			return (get_exit_status(status));
		}
	}
	return (ENO_GENERAL);
}

int	exec_node(t_node *tree, bool piped)
{
	int	status;

	if (!tree)
		return (1);
	if (tree->type == N_PIPE)
		return (exec_pipeline(tree));
	else if (tree->type == N_AND)
	{
		status = exec_node(tree->left, false);
		if (status == ENO_SUCCESS)
			return (exec_node(tree->right, false));
		return (status);
	}
	else if (tree->type == N_OR)
	{
		status = exec_node(tree->left, false);
		if (status == ENO_SUCCESS)
			return (status);
		return (exec_node(tree->right, false));
	}
	else
		return (exec_simple_cmd(tree, piped));
	return (ENO_GENERAL);
}
