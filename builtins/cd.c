/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:39:37 by gmunoz            #+#    #+#             */
/*   Updated: 2025/07/15 22:49:34 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	change_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	return (update_env_list("PWD", cwd, false), 0);
}

static int	cd_home(void)
{
	char	*home;

	update_env_list("OLDPWD", get_envlst_val("PWD"), false);
	home = get_envlst_val("HOME");
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home) == ENO_SUCCESS)
		return (update_env_list("PWD", home, false), 0);
	return (1);
}

static int	cd_err_msg(char *err_msg)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return (1);
}

int	ft_cd(char *path)
{
	if (!path)
		return (cd_home());
	if (chdir(path) != ENO_SUCCESS)
		return (cd_err_msg(path));
	update_env_list("OLDPWD", get_envlst_val("PWD"), false);
	return (change_pwd());
}
