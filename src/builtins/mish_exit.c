/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:08:19 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/24 11:48:22 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mish_exit(t_data *mish, t_scmd cmd)
{
	if (cmd.full_cmd[1] != NULL)
	{
		ft_putstr_fd("exit command takes no input\n", STDERR_FILENO);
		handle_exit(mish, NULL, SUCCESS, NOT_EXIT);
		return ;
	}
	handle_exit(mish, NULL, SUCCESS, IS_EXIT);
}
