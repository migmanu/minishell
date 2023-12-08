/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:50:52 by migmanu           #+#    #+#             */
/*   Updated: 2023/12/08 14:50:32 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_signal;

int	main(int argc, char *argv[], char *envp[])
{
	t_data	mish;
	char	*line;

	if (argc != 1)
		handle_exit(NULL, argv[1], INV_ARGS, IS_EXIT);
	init_mish(&mish, argv, envp);
	while (1)
	{
		g_signal = 0;
		config_signals_input();
		line = init_prompt(&mish);
		if (!line)
			break ;
		input_handler(line, &mish);
		executor(&mish);
		if (g_signal == SIGINT)
			mish.exit_status = 128 + g_signal;
	}
	handle_exit(&mish, NULL, SUCCESS, IS_EXIT);
	return (0);
}
