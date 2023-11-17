/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:49:09 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/17 21:23:55 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern char	**environ; // temp way of getting enviroment variables

void	exec_s_cmds(t_data *mish, t_scmd *cmd)
{
	printf("exec_s_cmds init, path: %s\n", cmd->path);
	cmd->path = get_path(mish, cmd->full_cmd[0]);
	if (execve(cmd->path, cmd->full_cmd, environ) != 0)
	{
		if (execve(cmd->full_cmd[0], cmd->full_cmd, environ) != 0)
		{
			mish_error(mish, "command executable not found", 7, 0); // check error code
		}
	}
}

void	fork_s_cmds(t_data *mish, t_scmd *cmd)
{
	printf("fork_s_cmds init\n");
	int	pid;

	pid = fork();
	if (pid == -1)
		mish_error(mish, NULL, FORK_ERR, 0);
	if (pid == 0)
	{
		dup_s_cmds(cmd);
		exec_s_cmds(mish, cmd);
	}
	else
	{
		if (cmd->out_fd != STDOUT_FILENO)
			close(cmd->out_fd);
		if (cmd->in_fd != STDIN_FILENO)
			close(cmd->in_fd);
		return ;
	}
}

void	exec_builtin(t_data *mish, t_scmd *cmd)
{
	//dup_s_cmds(cmd);
	builtins_router(mish, *cmd);
	printf("cmd in%d, out %d\n", cmd->in_fd, cmd->out_fd);
	if (cmd->out_fd != STDOUT_FILENO)
		close(cmd->out_fd);
	if (cmd->in_fd != STDIN_FILENO)
		close(cmd->in_fd);
}

void	executor_loop(t_data *mish, int fds[2])
{
	t_scmd	*cmd;
	t_list	*curr;
	t_scmd	*next_cmd;

	curr = mish->cmds;
	while (curr)
	{
		cmd = curr->content;
		printf("cmd is: %s\n", cmd->full_cmd[0]);
		if (curr->next != NULL)
		{
			next_cmd = curr->next->content;
			pipe(fds);
			if (cmd->out_fd == STDOUT_FILENO)
			{
				cmd->out_fd = fds[1];
			}
			if (next_cmd->in_fd == STDIN_FILENO)
			{
				next_cmd->in_fd = fds[0];
			}
		}
		if (check_if_builtin(cmd->full_cmd[0]) == 0)
		{
			exec_builtin(mish, cmd);
			return ;
		}
		fork_s_cmds(mish, cmd);
		curr = curr->next;
	}
}

void	executor(t_data *mish)
{
	int		status;
	int		fds[2];

	executor_loop(mish, fds);
	while (mish->cmds)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) == 1)
			g_exit_status = WEXITSTATUS(status);
		printf("g_exit_status %d\n", g_exit_status);
		mish->cmds = mish->cmds->next;
	}
}
