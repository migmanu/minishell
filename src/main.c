/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:50:52 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/14 19:14:34 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit;

int	main(int argc, char *argv[], char *envp[])
{
	t_data	mish;
	char	*line;

	g_exit = 0;
	if (argc != 1)
		mish_error(NULL, argv[1], INV_ARGS, 1);
	init_mish(&mish, envp);
	while (1 && g_exit == 0)
	{
		printf("g_exit is %d", g_exit);
		config_signals();
		line = init_prompt(&mish);
		//input_handler(line, &mish);
		create_mock_mish(&mish, line);
		executor_router(&mish);
	}
	return (0);
}
