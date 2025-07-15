/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:40:00 by guido             #+#    #+#             */
/*   Updated: 2025/07/15 22:55:46 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	append_identifier(char **line_ptr, t_token **token_list)
{
	char	*tmp_line;
	char	*value;
	t_token	*token;
	size_t	i;

	tmp_line = *line_ptr;
	i = 0;
	while (tmp_line[i] && !is_separator(tmp_line + i))
	{
		if (is_quote(tmp_line[i]))
		{
			if (!skip_quotes(tmp_line, &i))
				return (print_quote_err(tmp_line[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = new_token(value, T_IDENTIFIER);
	if (!token)
		return (free(value), 0);
	*line_ptr += i;
	return (token_list_add_back(token_list, token), 1);
}

int	append_separator(t_token_type type, char **line_ptr, t_token **token_list)
{
	t_token	*token;

	token = new_token(NULL, type);
	if (!token)
		return (0);
	token_list_add_back(token_list, token);
	(*line_ptr)++;
	if (type == T_DLESS || type == T_DGREAT || type == T_AND || type == T_OR)
		(*line_ptr)++;
	return (1);
}
