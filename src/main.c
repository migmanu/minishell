/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:50:52 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/10 15:26:04 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	mish;
	t_scmd	scmd;

	mish.scmd = &scmd;
	if (argc != 1)
		mish_error(NULL, argv[1], INV_ARGS, 1);
	init_mish(&mish, envp);
	executor_router(&mish);
	init_prompt(&mish);
	return (0);
}
