/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:08:05 by guido             #+#    #+#             */
/*   Updated: 2025/07/15 22:45:16 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	env_entry_exists(char *key)
{
	t_env	*envlst;

	envlst = g_minishell.envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (true);
		envlst = envlst->next;
	}
	return (false);
}

char	*get_envlst_val(char *key)
{
	t_env	*envlst;

	envlst = g_minishell.envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

static t_env	*envlst_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = lst_mng(ft_strdup(key), false);
	if (value)
		new->value = lst_mng(ft_strdup(value), false);
	new->next = NULL;
	return (new);
}

void	envlst_back(t_env *new)
{
	t_env	*current;

	if (!g_minishell.envlst)
	{
		g_minishell.envlst = new;
		return ;
	}
	current = g_minishell.envlst;
	while (current && current->next)
		current = current->next;
	current->next = new;
}

void	update_env_list(char *key, char *value, bool create)
{
	t_env	*envlst;

	envlst = g_minishell.envlst;
	while (envlst)
	{
		if (ft_strcmp(envlst->key, key) == 0)
		{
			if (value)
				envlst->value = lst_mng(ft_strdup(value), false);
			return ;
		}
		envlst = envlst->next;
	}
	if (create)
		envlst_back(envlst_new(key, value));
}
