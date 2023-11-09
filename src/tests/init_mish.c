/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:51:02 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/08 21:51:20 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	get_mish_pid(t_data *mish)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		hashmap_free_table(mish->env);
		exit(FAILURE);
	}
	if (pid == 0)
	{
		hashmap_free_table(mish->env);
		exit(FAILURE);
	}
	waitpid(pid, NULL, 0);
	mish->pid = pid - 1;
}

// TODO: Handling not envp
void	init_mish(t_data *mish, char *envp[])
{
	mish->cmds = NULL;
	mish->env = env_to_hash(envp);
	get_mish_pid(mish);
}
