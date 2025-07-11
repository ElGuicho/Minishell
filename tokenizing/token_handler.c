/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guido <guido@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:52:34 by guido             #+#    #+#             */
/*   Updated: 2025/07/11 18:41:03 by guido            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
		if (c == '\t' || c == '\n' || c == '\v'
			|| c == '\f' || c == '\r' || c == ' ')
			return (1);
		return (0);
}

int	handle_separator(char **line, t_token **token_list)
{
	if (!ft_strncmp(*line_ptr, "<<", 2))
		return (append_separator(T_DLESS, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">>", 2))
		return (append_separator(T_DGREAT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "<", 1))
		return (append_separator(T_LESS, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">", 1))
		return (append_separator(T_GREAT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "(", 1))
		return (append_separator(T_O_PARENT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, ")", 1))
		return (append_separator(T_C_PARENT, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "&&", 2))
		return (append_separator(T_AND, line_ptr, token_list) && 1);
	else if (!ft_strncmp(*line_ptr, "||", 2))
		return (append_separator(T_OR, line_ptr, token_list) && 1);
	else
		return (append_separator(T_PIPE, line_ptr, token_list) && 1);
}

t_token *token_handler(char *line)
{
	int		error;
	t_token	*token_list;

	error = 0;
	token_list = NULL;
	while (*line)
	{
		if (error)
			return (clear_token_list(&token_list), NULL);
		if (ft_isspace(*line))
			skip_spaces(&line);
		else if (!ft_strncmp(line, "<", 1) || !ft_strncmp(line, ">", 1)
			|| !ft_strncmp(line, "|", 1) || !ft_strncmp(line, "&&", 2)
			|| !ft_strncmp(line, "(", 1) || !ft_strncmp(line, ")", 1))
			error = (!handle_separator(&line, &token_list) && 1);
		else
			error = (!append_identifier(&line, &token_list) && 1);
	}
	return (token_list);
}