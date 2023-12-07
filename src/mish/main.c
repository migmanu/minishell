/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:50:52 by migmanu           #+#    #+#             */
/*   Updated: 2023/12/07 12:35:14 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_exit_status;

int	main(int argc, char *argv[], char *envp[])
{
	t_data	mish;
	char	*line;

	if (argc != 1)
		handle_exit(NULL, argv[1], INV_ARGS, IS_EXIT);
	init_mish(&mish, argv, envp);
	while (1)
	{
		mish.in_cmd = 0;
		config_signals_input();
		line = init_prompt(&mish);
		if (!line)
			break ;
		mish.in_cmd = 1;
		if (line[0] == '\0')
			mish.in_cmd = 0;
		input_handler(line, &mish);
		executor(&mish);
		if (mish.cmds)
			ft_lstclear(&mish.cmds, free_scmd);
	}
	handle_exit(&mish, NULL, SUCCESS, IS_EXIT);
	return (0);
}
