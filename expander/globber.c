/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:38:42 by gmunoz            #+#    #+#             */
/*   Updated: 2025/07/14 20:42:35 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static bool	matches_visibility(char *pattern, char *str)
{
	if ((pattern[0] == '.' && str[0] == '.')
		|| (pattern[0] != '.' && str[0] != '.'))
		return (true);
	return (false);
}

static bool	set_direntry(struct dirent **entry, DIR *dir)
{
	*entry = readdir(dir);
	return (true);
}

static char	**globber_helper(char *str)
{
	char			**returned;
	DIR				*dir;
	struct dirent	*entry;
	size_t			match_count;

	match_count = match_counter(str);
	if (!contains_asterisk(str) || !match_count)
	{
		returned = (char **)ft_calloc(2, sizeof(char *));
		returned[0] = ft_strdup(str);
		return (returned);
	}
	else
	{
		dir = opendir(".");
		returned = (char **)ft_calloc(match_count + 1, sizeof(char *));
		match_count = 0;
		while (set_direntry(&entry, dir) && entry)
			if (match_star(str, entry->d_name)
				&& matches_visibility(str, entry->d_name))
				returned[match_count++] = ft_strdup(entry->d_name);
		closedir(dir);
	}
	return (returned);
}

char	**globber(char **expanded)
{
	size_t	i;
	size_t	expanded_len;
	char	***globbed;

	expanded_len = str_arr_len(expanded);
	globbed = (char ***)ft_calloc(expanded_len + 1, sizeof(char **));
	i = 0;
	while (expanded[i])
	{
		globbed[i] = globber_helper(expanded[i]);
		i++;
	}
	return (free_char2(expanded), join_str_arrs(globbed));
}
