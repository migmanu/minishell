/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:08:19 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/10 12:49:11 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mish_exit(t_data *mish, t_scmd cmd)
{
	int	i;

	i = 1;
	if (cmd.full_cmd[1] != NULL && ft_isdigit(ft_atoi(cmd.full_cmd[1])) == 0)
	{
		handle_exit(mish, NULL, SUCCESS, NOT_EXIT);
		exit((unsigned char)ft_atoi(cmd.full_cmd[1]));
	}
	else if (cmd.full_cmd[1] != NULL)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("mish: exit: ", STDERR_FILENO);
		while (cmd.full_cmd[i] != NULL)
		{
			ft_putstr_fd(cmd.full_cmd[1], STDERR_FILENO);
			ft_putstr_fd(" ", STDERR_FILENO);
			i++;
		}
		ft_putstr_fd(": arguments not valid\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd("exit\n", STDIN_FILENO);
	handle_exit(mish, NULL, SUCCESS, IS_EXIT);
}
