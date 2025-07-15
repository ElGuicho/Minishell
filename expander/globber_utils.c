/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globber_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:20:38 by gmunoz            #+#    #+#             */
/*   Updated: 2025/07/15 23:09:26 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	multi_arr_strs_count(char ***str_arrs)
{
	size_t	i;
	size_t	j;
	size_t	strs_count;

	i = 0;
	strs_count = 0;
	while (str_arrs[i])
	{
		j = 0;
		while (str_arrs[i][j])
			j++;
		strs_count += j;
		i++;
	}
	return (strs_count);
}

char	**join_str_arrs(char ***str_arrs)
{
	size_t	i;
	size_t	j;
	size_t	strs_count;
	char	**joined;

	strs_count = multi_arr_strs_count(str_arrs);
	joined = (char **)ft_calloc(strs_count + 1, sizeof(char *));
	i = 0;
	strs_count = 0;
	while (str_arrs[i])
	{
		j = 0;
		while (str_arrs[i][j])
		{
			joined[strs_count + j] = ft_strdup(str_arrs[i][j]);
			j++;
		}
		strs_count += j;
		i++;
	}
	return (ft_free_char3(str_arrs), joined);
}

bool	contains_asterisk(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

size_t	match_counter(char *pattern)
{
	DIR				*dir;
	size_t			match_count;
	struct dirent	*entry;

	match_count = 0;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		if (match_star(pattern, entry->d_name))
			match_count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (match_count);
}

size_t	str_arr_len(char **str_arr)
{
	size_t	i;

	i = 0;
	while (str_arr[i])
		i++;
	return (i);
}
