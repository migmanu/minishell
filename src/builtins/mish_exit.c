/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:08:19 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/09 12:59:59 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mish_exit(t_data *mish, t_scmd cmd)
{
	if (cmd.full_cmd[1] != NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("mish: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd.full_cmd[1], STDERR_FILENO);
		ft_putstr_fd(": arguments not valid\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd("exit\n", STDIN_FILENO);
	handle_exit(mish, NULL, SUCCESS, IS_EXIT);
}
