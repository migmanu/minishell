/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:49:09 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/08 15:51:29 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

void	exec_smcds(t_data *data)
{
	char	**cmd;

	cmd = ft_split(data->scmds->full_cmd, ' ');
	execve(data->scmds->path, cmd, data->envp);
	// handle error
}

void	dup_scmds(t_data *data, int fds[])
{
	// TODO: add builtin check
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	exec_smcds(data);
}

void	fork_cmd(t_data *data, int fds[])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return ; // TODO: handle error
	if (pid == 0)
	{
		dup_scmds(data, fds);
	}
}

void	executor_router(t_data *data)
{
	int	fds[2] = {STDIN_FILENO, STDOUT_FILENO};// fixed to stdin and stdout for now
	if (pipe(fds) == -1)
		return ; // TODO: handle error
	while (data->scmds)
	{
		fork_cmd(data, fds);
		data->scmds = data->scmds->next;
	}
}
