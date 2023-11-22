/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:49:09 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/22 20:06:55 by jmigoya-         ###   ########.fr       */
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

void	fork_cmds(t_data *mish, t_scmd *cmd, int pids[], int c)
{
	pids[c] = fork();
	if (pids[c] == -1)
		handle_exit(mish, NULL, FORK_ERR, NOT_EXIT);
	if (pids[c] == 0)
	{
		dup_cmd(cmd);
		exec_cmd(mish, cmd);
	}
	else
	{
		if (cmd->out_fd != STDOUT_FILENO)
			close(cmd->out_fd);
		if (cmd->in_fd != STDIN_FILENO)
			close(cmd->in_fd);
	}
}

void	executor_loop(t_data *mish, int pids[], int c)
{
	int		i;
	t_list	*curr;

	curr = mish->cmds;
	i = 0;
	while (curr && i < c)
	{
		fork_cmds(mish, curr->content, pids, i);
		curr = curr->next;
		i++;
	}
}

void	wait_loop(int pids[], int c)
{
	int		status;
	int		i;

	i = 0;
	while (i < c - 1)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	waitpid(pids[i], &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

void	executor(t_data *mish)
{
	t_scmd	*first;
	int		fds[2];
	int		*pids;
	int		c;

	c = 0;
	if (!mish->cmds)
		return ;
	first = mish->cmds->content;
	if (mish->cmds->next == NULL && check_if_builtin(first->full_cmd[0]) == 0)
	{
		builtins_router(mish, *first, NOT_EXIT);
		return ;
	}
	set_file_descriptors(mish, fds, &c);
	pids = malloc(sizeof(int) * c);
	if (!pids)
		handle_exit(mish, "malloc failed!", FAILURE, NOT_EXIT);
	executor_loop(mish, pids, c);
	wait_loop(pids, c);
	free(pids);
}
