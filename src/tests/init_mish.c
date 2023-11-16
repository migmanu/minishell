/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:33:52 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/16 13:24:07 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char	**environ; // temp way of getting enviroment variables

static void	get_sh_pid(t_data *mish)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		mish_error(mish, NULL, FORK_ERR, 1);
	if (pid == 0)
		mish_error(mish, NULL, FAILURE, 1);
	waitpid(pid, NULL, 0);
	mish->pid = pid - 1;
}

// TODO: Handling not envp
void	init_mish(t_data *mish, char *envp[])
{
	mish->cmds = NULL;
	mish->env = env_to_hash(envp);
	get_sh_pid(mish);
	// WARNING: rest of function creates mock t_scmd for testing
}
