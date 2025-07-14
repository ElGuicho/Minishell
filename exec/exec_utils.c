/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:30:59 by guido             #+#    #+#             */
/*   Updated: 2025/07/14 22:42:17 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_delimiter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!*delimiter);
}

void	del(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	*garbage_collector(void *ptr, bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		ft_lstclear(&garbage_list, del);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
		return (ptr);
	}
}

void	*lst_mng(void *ptr, bool clean)
{
	static t_list	*garbage;

	if (clean)
	{
		ft_lstclear(&garbage, del);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage, ft_lstnew(ptr));
		return (ptr);
	}
}
