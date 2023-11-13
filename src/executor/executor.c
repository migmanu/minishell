/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:49:09 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/10 19:35:42 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char	**environ; // temp way of getting enviroment variables

void	exec_s_cmds(t_data *mish)
{
	t_scmd	*cmd;

	cmd = mish->cmds->content;
	printf("exec_s_cmds init\n");
	execve(cmd->path, cmd->full_cmd, environ); // TODO: change environ!
}

void	dup_s_cmds(t_data *mish, int fds[])
{
	printf("dup_s_cmds init\n");
	exec_s_cmds(mish);
	// TODO: add check for builtin cmds
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
}

void	fork_s_cmds(t_data *mish, int fds[])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return; // TODO: handle error
	if (pid == 0)
	{
		dup_s_cmds(mish, fds);
	}
	wait(0);
}

void	executor_router(t_data *mish)
{
	printf("executor_router init\n");
	int	fds[2] = {STDIN_FILENO, STDOUT_FILENO};// fixed to stdin and stdout for now
	if (pipe(fds) == -1)
		return ; // TODO: handle error
	while (mish->cmds)
	{
		fork_s_cmds(mish, fds);
		mish->cmds = mish->cmds->next;
	}
}
