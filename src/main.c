/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:50:52 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/15 18:50:17 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	mish;
	char	*line;

	if (argc != 1)
		mish_error(NULL, argv[1], INV_ARGS, 1);
	init_mish(&mish, envp);
	while (1)
	{
		config_signals();
		line = init_prompt(&mish);
		input_handler(line, &mish);
		//executor_router(&mish);
		// TODO: this clean all the cmds and also close fds of files but, i think
		// it should be provisional for now, this should be after the executor but inside
		// your function to have more cleaning main
		if (mish.cmds)
			ft_lstclear(&mish.cmds, free_scmd);
    if (line[0] == '\0')
      continue;
		//input_handler(line, &mish);
		create_mock_mish(&mish, line);
		executor_router(&mish);
	}
	return (0);
}
