/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guido <guido@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:09:42 by guido             #+#    #+#             */
/*   Updated: 2025/07/11 20:10:19 by guido            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

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
	}
	return (0);
}
