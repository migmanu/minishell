/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:08:19 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/14 19:16:41 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mish_exit(t_data *mish, t_scmd cmd)
{
	printf("mish_exit init\n");
	if (cmd.full_cmd[1] != NULL)
	{
		// handle error
		ft_putstr_fd("exit command takes no input\n", STDERR_FILENO);
		exit(ERROR);
	}
	g_exit = 1;
	printf("mish_exit set g_exit to %d\n", g_exit);
	handle_exit(mish, SUCCESS);
}
