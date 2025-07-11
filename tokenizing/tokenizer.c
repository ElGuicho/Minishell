/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guido <guido@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:40:47 by guido             #+#    #+#             */
/*   Updated: 2025/07/07 20:53:33 by guido            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(void)
{
	char *line;
	t_token *token_list;
	
	line = g_minishell.line;
	token_list = token_handler(line);
	free(line);
	g_minishell.line = NULL;
	return (token_list);
}
