/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:50:52 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/08 17:00:44 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_hashmap	*env;
	t_hashmap	*local_vars;

	if (argc != 1)
	{
		printf("minishell takes no arguments, you passed %s\n", argv[1]);
		exit(ERROR);
	}
	env = env_to_hash(envp);
	local_vars = hashmap_create_table(50);
	hashmap_print_table(env);
	init_promt("USER");
	(void)local_vars;
	return (0);
}
