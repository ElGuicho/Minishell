/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:50:18 by gmunoz            #+#    #+#             */
/*   Updated: 2025/07/15 23:15:42 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_redirection(t_node *node)
{
	t_io_node	*tmp_io;
	int			tmp_status;

	tmp_io = node->io_list;
	while (tmp_io)
	{
		if (tmp_io->type == IO_OUT
			&& ft_out(tmp_io, &tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_IN
			&& ft_in(tmp_io, &tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_APPEND
			&& ft_append(tmp_io, &tmp_status) != ENO_SUCCESS)
			return (tmp_status);
		else if (tmp_io->type == IO_HEREDOC)
			(dup2(tmp_io->here_doc, 0), close(tmp_io->here_doc));
		tmp_io = tmp_io->next;
	}
	return (ENO_SUCCESS);
}

void	reset_stds(bool piped)
{
	if (piped)
		return ;
	dup2(g_minishell.stdin, 0);
	dup2(g_minishell.stdout, 1);
}

static int	exec_child(t_node *node)
{
	t_path	path_status;
	int		tmp_status;
	int		fork_pid;

	g_minishell.signint_child = true;
	fork_pid = fork();
	if (!fork_pid)
	{
		tmp_status = check_redirection(node);
		if (tmp_status != ENO_SUCCESS)
			(clean_ms(), exit(ENO_GENERAL));
		path_status = get_path((node -> expanded_args)[0]);
		if (path_status.err.no != ENO_SUCCESS)
		{
			tmp_status = err_msg(path_status.err);
			(clean_ms(), exit(tmp_status));
		}
		if (execve(path_status.path, node -> expanded_args,
				g_minishell.environ) == -1)
			(clean_ms(), exit(1));
	}
	waitpid(fork_pid, &tmp_status, 0);
	g_minishell.signint_child = false;
	return (get_exit_status(tmp_status));
}

int	exec_simple_cmd(t_node *node, bool piped)
{
	int		tmp_status;

	if (!node -> expanded_args)
	{
		tmp_status = check_redirection(node);
		return (reset_stds(piped), (tmp_status && ENO_GENERAL));
	}
	else if (is_builtin((node -> expanded_args)[0]))
	{
		tmp_status = check_redirection(node);
		if (tmp_status != ENO_SUCCESS)
			return (reset_stds(piped), ENO_GENERAL);
		tmp_status = exec_builtin(node -> expanded_args);
		return (reset_stds(piped), tmp_status);
	}
	else
		return (exec_child(node));
}
