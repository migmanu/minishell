/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:49:09 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/21 14:08:35 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

extern char	**environ; // temp way of getting enviroment variables

void	exec_cmd(t_data *mish, t_scmd *cmd)
{
	printf("exec_cmd init, cmd %s, in %d out %d\n", \
		cmd->full_cmd[0], cmd->in_fd, cmd->out_fd);
	builtins_router(mish, *cmd, IS_EXIT);
	cmd->path = get_path(mish, cmd->full_cmd[0]);
	if (execve(cmd->path, cmd->full_cmd, environ) != 0)
	{
		if (execve(cmd->full_cmd[0], cmd->full_cmd, environ) != 0)
		{
			handle_exit(mish, "command not found", NO_FILE, IS_EXIT);
		}
	}
}

void	fork_cmds(t_data *mish, t_scmd *cmd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		handle_exit(mish, NULL, FORK_ERR, NOT_EXIT);
	if (pid == 0)
	{
		dup_cmd(cmd);
		exec_cmd(mish, cmd);
	}
	else
	{
		if (check_if_builtin(cmd->full_cmd[0]) == 0)
			wait(0);
		if (cmd->out_fd != STDOUT_FILENO)
			close(cmd->out_fd);
		if (cmd->in_fd != STDIN_FILENO)
			close(cmd->in_fd);
	}
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
		fork_cmds(mish, cmd);
		curr = curr->next;
	}
}

void	wait_loop(t_list *cmds)
{
	t_scmd	*curr;
	int		status;

	while (cmds)
	{
		curr = cmds->content;
		if (check_if_builtin(curr->full_cmd[0]) != 0)
		{
			printf("waiting\n");
			waitpid(-1, &status, 0);
			if (WIFEXITED(status) == 1)
				g_exit_status = WEXITSTATUS(status);
		}
		printf("g_exit_status %d\n", g_exit_status);
		cmds = cmds->next;
	}
}

void	executor(t_data *mish)
{
	t_scmd	*first;
	int		fds[2];

	if (!mish->cmds)
		return ;
	first = mish->cmds->content;
	if (mish->cmds->next == NULL && check_if_builtin(first->full_cmd[0]) == 0)
	{
		printf("first is builtin\n");
		builtins_router(mish, *first, NOT_EXIT);
		return ;
	}
	executor_loop(mish, fds);
	wait_loop(mish->cmds);
}
