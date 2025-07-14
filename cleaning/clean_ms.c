/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 22:38:47 by gmunoz            #+#    #+#             */
/*   Updated: 2025/07/14 22:44:13 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_envlst(void)
{
	t_env	*envlst;
	t_env	*envlst_tofree;

	envlst = g_minishell.envlst;
	while (envlst)
	{
		envlst_tofree = envlst;
		envlst = envlst->next;
		free(envlst_tofree);
	}
	g_minishell.envlst = NULL;
}

void	clean_ms(void)
{
	garbage_collector(NULL, true);
	clear_ast(&g_minishell.ast);
	clear_envlst();
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.original_term);
}
