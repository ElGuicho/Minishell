/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:40:47 by guido             #+#    #+#             */
/*   Updated: 2025/07/15 22:56:24 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*tokenize(void)
{
	char	*line;
	t_token	*token_list;

	line = g_minishell.line;
	token_list = token_handler(line);
	free(line);
	g_minishell.line = NULL;
	return (token_list);
}
