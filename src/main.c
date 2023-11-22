/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:08:49 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/21 20:23:53 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status;

int	main(int argc, char *argv[], char *envp[])
{
	t_data	mish;
	char	*line;

	if (argc != 1)
		handle_exit(NULL, argv[1], INV_ARGS, IS_EXIT);
	init_mish(&mish, envp);
	while (1)
	{
		config_signals();
		line = init_prompt(&mish);
		if (!line)
		{
			continue ;
		}
		input_handler(line, &mish);
		executor(&mish);
		// TODO: this clean all the cmds and also close fds of files but, i think
		// it should be provisional for now, this should be after the executor but
		// inside your function to have more cleaning main
		if (mish.cmds)
			ft_lstclear(&mish.cmds, free_scmd);
	}
	return (0);
}
