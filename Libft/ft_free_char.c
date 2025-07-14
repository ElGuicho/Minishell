/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:56:13 by gmunoz            #+#    #+#             */
/*   Updated: 2025/07/14 20:56:25 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_char2(char **tofree)
{
	size_t	i;

	if (!tofree)
		return ;
	i = 0;
	while (tofree[i])
		free(tofree[i++]);
	free(tofree);
}

void	ft_free_char3(char ***tofree)
{
	size_t	i;

	if (!tofree)
		return ;
	i = 0;
	while (tofree[i])
		ft_free_char2(tofree[i++]);
	free(tofree);
}
