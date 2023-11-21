/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:50:52 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/21 12:55:53 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status;

int	main(int argc, char *argv[], char *envp[])
{
	t_data	mish;
	char	*line;

	if (argc != 1)
		mish_error(NULL, argv[1], INV_ARGS, 1);
	init_mish(&mish, argv, envp);
	while (1)
	{
		config_signals();
		line = init_prompt(&mish);
		if (!line)
			break ;
		input_handler(line, &mish);
		// TODO: this clean all the cmds and also close fds of files but, i think
		// it should be provisional for now, this should be after the executor but
		// inside your function to have more cleaning main
		if (mish.cmds)
			ft_lstclear(&mish.cmds, free_scmd);
	}
	mish_error(&mish, NULL, SUCCESS, 1);
	return (0);
}
