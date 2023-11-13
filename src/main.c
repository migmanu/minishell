/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:50:52 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/10 19:31:21 by jmigoya-         ###   ########.fr       */
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
		//input_handler(line, &mish);
		create_mock_mish(&mish, line);
		executor_router(&mish);
	}
	return (0);
}
