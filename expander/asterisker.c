/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:48:08 by gmunoz            #+#    #+#             */
/*   Updated: 2025/07/14 20:07:18 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static void	handle_pattern_quotes(char **pattern, char *quotes)
{
	if (**pattern == '"' || **pattern == '\'')
	{
		if (!*quotes)
			*quotes = *(*pattern)++;
		else
		{
			if (*quotes == **pattern)
			{
				*quotes = 0;
				(*pattern)++;
			}
		}
	}
}

static bool	handle_stars(char **pattern, char **last_wildcard,
			char **last_match, char *str)
{
	while (**pattern == '*')
		(*pattern)++;
	if (!**pattern)
		return (true);
	*last_wildcard = *pattern;
	*last_match = str;
	return (false);
}

static bool	pattern_match_exists(char **pattern, char **last_wildcard,
			char **last_match, char **str)
{
	if (**pattern == **str)
	{
		(*pattern)++;
		(*str)++;
		return (true);
	}
	else if (*last_wildcard)
	{
		*str = ++(*last_match);
		*pattern = *last_wildcard;
		return (true);
	}
	else
		return (false);
}

bool	match_star(char *pattern, char *str)
{
	char	*last_wildcard;
	char	*last_match;
	char	quotes;

	quotes = 0;
	last_wildcard = NULL;
	last_match = NULL;
	while (*str)
	{
		handle_pattern_quotes(&pattern, &quotes);
		if (*pattern == '*' && !quotes
			&& handle_stars(&pattern, &last_wildcard, &last_match, str))
			return (true);
		else if (!pattern_match_exists(
			&pattern, &last_wildcard, &last_match, &str))
			return (false);
	}
	if (*pattern == '*')
		while (*pattern == '*')
			pattern++;
	return (!*pattern);
}
