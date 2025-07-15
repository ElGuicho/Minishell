/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:09:42 by guido             #+#    #+#             */
/*   Updated: 2025/07/15 22:38:25 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

t_minishell	g_minishell;

static void	init_minishell(char **env)
{
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	g_minishell.environ = env;
	init_env_list();
	g_minishell.stdin = dup(0);
	g_minishell.stdout = dup(1);
	tcgetattr(STDIN_FILENO, &g_minishell.original_term);
}

static void	start_execution(void)
{
	signal(SIGQUIT, sigquit_handler);
	init_tree(g_minishell.ast);
	if (g_minishell.heredoc_sigint)
	{
		clear_ast(&g_minishell.ast);
		g_minishell.heredoc_sigint = false;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.original_term);
	g_minishell.exit_s = exec_node(g_minishell.ast, false);
	clear_ast(&g_minishell.ast);
}

int	main(int argc, char **argv, char **env)
{
	((void)argc, (void)argv);
	init_minishell(env);
	while (1)
	{
		init_signals();
		g_minishell.line = readline(PROMPT);
		if (!g_minishell.line)
			(clean_ms(), ft_putstr_fd("exit\n", 1), exit(g_minishell.exit_s));
		if (g_minishell.line[0])
			add_history(g_minishell.line);
		g_minishell.tokens = tokenize();
		if (!g_minishell.tokens)
			continue ;
		g_minishell.ast = ft_parse();
		if (g_minishell.parse_err.type)
		{
			handle_parse_error();
			continue ;
		}
		start_execution();
	}
	lst_mng(NULL, true);
	return (clean_ms(), g_minishell.exit_s);
}
