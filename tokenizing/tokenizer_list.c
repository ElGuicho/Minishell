/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:55:36 by guido             #+#    #+#             */
/*   Updated: 2025/07/15 22:55:59 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	token_list_add_back(t_token **lst, t_token *new_token)
{
	t_token	*current;

	if (!*lst)
	{
		*lst = new_token;
		return ;
	}
	current = *lst;
	while (current && current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	return (new_token);
}

void	clear_token_list(t_token **lst)
{
	t_token	*current;
	t_token	*next;

	current = *lst;
	if (!current)
		return ;
	while (current)
	{
		free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}
