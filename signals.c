/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:17:32 by guido             #+#    #+#             */
/*   Updated: 2025/07/14 21:48:34 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", 1);
}

static void	sigint_handler(int sig)
{
	(void)sig;
	if (g_minishell.signint_child)
	{
		ft_putstr_fd("\n", 1);
		g_minishell.signint_child = false;
		g_minishell.heredoc_sigint = true;
	}
	else
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signals()
{
	struct termios	term;

	term = g_minishell.original_term;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	g_minishell.heredoc_sigint = false;
	g_minishell.signint_child = false;
	signal(SIGINT, sigint_handler);
}
