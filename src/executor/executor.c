/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:49:09 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/16 16:52:00 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

extern char	**environ; // temp way of getting enviroment variables

char	*get_path(t_data *mish, char *cmd)
{
	char	**path_vec;
	char	*tmp_path;
	char	*path;
	int		i;

	i = 0;
	path_vec = ft_split(hashmap_search(mish->env, "PATH") + 5, ':');
	i = 0;
	while (path_vec[i])
	{
		tmp_path = ft_strjoin("/", cmd);
		path = ft_strjoin(path_vec[i], tmp_path);
		free(tmp_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (path_vec[i])
		free(path_vec[i++]);
	free(path_vec);
	return (NULL);
}

void	exec_s_cmds(t_scmd *cmd)
{
	printf("exec_s_cmds init, path: %s\n", cmd->path);
	execve(cmd->path, cmd->full_cmd, environ); // TODO: change environ!
}

void	dup_s_cmds(t_scmd *cmd)
{
	printf("dup_s_cmds init, in: %d | out: %d\n", cmd->in_fd, cmd->out_fd);
	// TODO: add check for builtin cmds
	if (cmd->out_fd != STDOUT_FILENO)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
	if (cmd->in_fd != STDIN_FILENO)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
	exec_s_cmds(cmd);
}

void	fork_s_cmds(t_data *mish, t_scmd *cmd)
{
	int	pid;

	builtins_router(mish, *cmd);
	pid = fork();
	if (pid == -1)
		return ; // TODO: handle error
	if (pid == 0)
	{
		dup_s_cmds(cmd);
	}
	else
	{
		wait(0);
	}
}

void	executor_router(t_data *mish)
{
	t_scmd	*cmd;
	t_scmd	*next_cmd;
	int		fds[2];

	printf("executor_router init\n");
	while (mish->cmds)
	{
		printf("while init\n");
		cmd = mish->cmds->content;
		cmd->path = get_path(mish, cmd->full_cmd[0]);
		if (mish->cmds->next != NULL)
		{
			next_cmd = mish->cmds->next->content;
			pipe(fds);
			cmd->out_fd = fds[1];
			next_cmd->in_fd = fds[0];
		}
		fork_s_cmds(mish, cmd);
		mish->cmds = mish->cmds->next;
	}
}
