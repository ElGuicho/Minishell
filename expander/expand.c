/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:16:28 by guido             #+#    #+#             */
/*   Updated: 2025/07/14 21:56:59 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_dollar(char *str, size_t *i)
{
	size_t	start;
	char	*var;
	char	*env_val;

	(*i)++;
	if (ft_isdigit(str[*i]) || str[*i] == '@')
	{
		(*i)++;
		return (ft_strdup(""));
	}
	else if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(g_minishell.exit_s));
	}
	else if (!is_valid_var_char(str[*i]))
		return (ft_strdup("$"));
	start = *i;
	while (is_valid_var_char(str[*i]))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	env_val = get_envlst_val(var);
	if (!env_val)
		return (free(var), ft_strdup(""));
	return (free(var), ft_strdup(env_val));
}

char	*ft_strjoin_f(char *s1, char *s2)
{
	char	*joined;
	size_t	total_length;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	total_length = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = ft_calloc(total_length, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = 0;
	return (free(s1), free(s2), joined);
}

static char	*cmd_pre_expander(char *str)
{
	char	*ret;
	size_t	i;

	ret = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			ret = ft_strjoin_f(ret, handle_squotes(str, &i));
		else if (str[i] == '"')
			ret = ft_strjoin_f(ret, handle_dquotes(str, &i));
		else if (str[i] == '$')
			ret = ft_strjoin_f(ret, handle_dollar(str, &i));
		else
			ret = ft_strjoin_f(ret, handle_normal_str(str, &i));
	}
	return (ret);
}

char	**expand(char *str)
{
	char	**expanded;
	char	**globbed;
	size_t	i;

	str = cmd_pre_expander(str);
	if (!str)
		return (NULL);
	str = clean_empty_strs(str);
	if (!str)
		return (NULL);
	expanded = expander_split(str);
	free(str);
	if (!expanded)
		return (NULL);
	globbed = globber(expanded);
	if (!globbed)
		return (NULL);
	i = 0;
	while (globbed[i])
	{
		globbed[i] = strip_quotes(globbed[i]);
		i++;
	}
	return (globbed);
}
