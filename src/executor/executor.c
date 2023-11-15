/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:49:09 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/14 20:17:37 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

extern char	**environ; // temp way of getting enviroment variables

void	exec_s_cmds(t_data *mish, t_scmd *cmd)
{
	printf("exec_s_cmds init\n");
	if (mish->pid)
		mish->pid++;
	execve(cmd->path, cmd->full_cmd, environ); // TODO: change environ!
}

void	dup_s_cmds(t_data *mish, t_scmd *cmd, int fds[])
{
	printf("dup_s_cmds init\n");
	// TODO: add check for builtin cmds
	if (fds[1] != STDOUT_FILENO)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
	}
	if (fds[0] != STDIN_FILENO)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	exec_s_cmds(mish, cmd);
}

void	fork_s_cmds(t_data *mish, t_scmd *cmd, int fds[])
{
	int	pid;

	builtins_router(mish, *cmd);
	pid = fork();
	if (pid == -1)
		return ; // TODO: handle error
	if (pid == 0)
	{
		dup_s_cmds(mish, cmd, fds);
	}
	else
	{
		wait(0);
	}
}

void	executor_router(t_data *mish)
{
	printf("executor_router init\n");
	int	fds[2] = {STDIN_FILENO, STDOUT_FILENO};// fixed to stdin and stdout for now
	while (mish->cmds)
	{
		fork_s_cmds(mish, mish->cmds->content, fds);
		mish->cmds = mish->cmds->next;
	}
}
