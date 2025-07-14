/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:29:13 by guido             #+#    #+#             */
/*   Updated: 2025/07/14 21:51:26 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (lst_mng(ft_substr(str, 0, i), false));
		i++;
	}
	return (ft_strdup(str));
}

char	*get_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (lst_mng(ft_substr(str, i, ft_strlen(str) - i), false));
		}
		i++;
	}
	return (NULL);
}

void	init_env_list(void)
{
	int		i;
	char	**environ;
	char	*key;
	char	*value;

	environ = g_minishell.environ;
	if (!environ)
		return ;
	while (environ[i])
	{
		key = get_key(environ[i]);
		value = get_value(environ[i]);
		uptdate_env_list(key, value, true);
		i++;
	}
}