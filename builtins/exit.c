/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 23:01:18 by gmunoz            #+#    #+#             */
/*   Updated: 2025/07/15 23:04:42 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static bool	isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	skip_spaces_and_get_sign(char *s, int *i, int *sign)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}

static int	exittoi(char *s)
{
	int					i;
	int					sign;
	int					exit_s;
	unsigned long long	result;

	i = 0;
	sign = 1;
	skip_spaces_and_get_sign(s, &i, &sign);
	if (!isnumber(s + i))
	{
		exit_s = err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
		(clean_ms(), exit(exit_s));
	}
	result = 0;
	while (s[i])
	{
		result = (result * 10) + (s[i] - '0');
		if (result > LONG_MAX)
		{
			exit_s = err_msg((t_err){ENO_EXEC_255, ERRMSG_NUMERIC_REQUI, s});
			(clean_ms(), exit(exit_s));
		}
		i++;
	}
	return ((result * sign) % 256);
}

void	ft_exit(char **args)
{
	int	exit_s;

	exit_s = g_minishell.exit_s;
	if (args[1])
	{
		if (args[2] && isnumber(args[1]))
		{
			exit_s = err_msg(
					(t_err){ENO_GENERAL, ERRMSG_TOO_MANY_ARGS, NULL});
			(clean_ms(), exit(exit_s));
		}
		else
			exit_s = exittoi(args[1]);
	}
	(clean_ms(), exit(exit_s));
}
