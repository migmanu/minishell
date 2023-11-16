/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:51:02 by sebasnadu         #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/12 17:11:58 by sebasnadu        ###   ########.fr       */
=======
/*   Updated: 2023/11/10 18:55:19 by jmigoya-         ###   ########.fr       */
>>>>>>> upstream/main
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

<<<<<<< HEAD
extern char	**environ; // temp way of getting enviroment variables

static void	get_sh_pid(t_data *mish)
=======
static void	get_mish_pid(t_data *mish)
>>>>>>> upstream/main
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
<<<<<<< HEAD
	get_sh_pid(mish);
	// WARNING: rest of function creates mock t_scmd for testing
	full_cmd = ft_split("ls -l", ' ');
	if (full_cmd == NULL)
	{
		ft_putstr_fd("Error creating fake cmd", STDERR_FILENO);
		exit(ERROR);
	}
	mish->pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(mish->pwd, PATH_MAX);
	mish->scmd->in_fd = 0;
	mish->scmd->out_fd = 1;
	mish->scmd->full_cmd = full_cmd;
	mish->scmd->path = get_cmd_path(mish->scmd->full_cmd[0], environ); // TODO: replace environ
=======
	get_mish_pid(mish);
>>>>>>> upstream/main
}
