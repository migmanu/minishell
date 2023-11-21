/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtis_router.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/1/13 14:01:08 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/21 16:42:19 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// returns 0 if the str corresponds to the name
// of a builtin function. 1 otherwise.
int	check_if_builtin(const char *str)
{
	if (ft_strncmp("echo", str, 4) == 0)
		return (0);
	if (ft_strncmp("cd", str, 2) == 0)
		return (0);
	if (ft_strncmp("pwd", str, 3) == 0)
		return (0);
	if (ft_strncmp("export", str, 6) == 0)
		return (0);
	if (ft_strncmp("unset", str, 5) == 0)
		return (0);
	if (ft_strncmp("env", str, 3) == 0)
		return (0);
	if (ft_strncmp("exit", str, 4) == 0)
		return (0);
	return (1);
}

int	builtins_router(t_data *mish, t_scmd cmd, int if_exit)
{
	if (ft_strncmp("echo", cmd.full_cmd[0], 4) == 0)
		mish_echo(mish, cmd, if_exit);
	if (ft_strncmp("cd", cmd.full_cmd[0], 2) == 0)
		mish_cd(mish, cmd, if_exit);
	if (ft_strncmp("pwd", cmd.full_cmd[0], 3) == 0)
		mish_pwd(mish, cmd, if_exit);
	if (ft_strncmp("export", cmd.full_cmd[0], 6) == 0)
		mish_export(mish, cmd, if_exit);
	if (ft_strncmp("unset", cmd.full_cmd[0], 5) == 0)
		mish_unset(mish, cmd, if_exit);
	if (ft_strncmp("env", cmd.full_cmd[0], 3) == 0)
		return (0);
	if (ft_strncmp("exit", cmd.full_cmd[0], 4) == 0)
		mish_exit(mish, cmd);
	return (0);
}
