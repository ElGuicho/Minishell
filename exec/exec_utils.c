/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guido <guido@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:30:59 by guido             #+#    #+#             */
/*   Updated: 2025/07/07 17:01:23 by guido            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
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