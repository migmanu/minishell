/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtis_router.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/1/13 14:01:08 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/14 18:50:28 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtins_router(t_data *mish, t_scmd cmd)
{
	printf("builtis_router init\n");
	if (ft_strncmp("echo", cmd.full_cmd[0], 4) == 0)
		return ; // call builtin
	if (ft_strncmp("cd", cmd.full_cmd[0], 2) == 0)
		mish_cd(mish, cmd);
	if (ft_strncmp("pwd", cmd.full_cmd[0], 3) == 0)
		mish_pwd(mish, cmd);
	if (ft_strncmp("export", cmd.full_cmd[0], 6) == 0)
		return ; // call builtin
	if (ft_strncmp("unset", cmd.full_cmd[0], 5) == 0)
		return ; // call builtin
	if (ft_strncmp("env", cmd.full_cmd[0], 3) == 0)
		return ; // call builtin
	if (ft_strncmp("exit", cmd.full_cmd[0], 4) == 0)
		mish_exit(mish, cmd);
	return ;
}
