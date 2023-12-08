/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:49:09 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/08 15:10:01 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// First goes for builtin functions. If none found, executes binary
// if one is found. It also checks for cases like '/' and prints
// proper error.
void	exec_cmd(t_data *mish, t_scmd *cmd)
{
	char	**env;

	if (cmd->full_cmd == NULL)
		handle_exit(mish, NULL, SUCCESS, IS_EXIT);
	builtins_router(mish, *cmd, IS_EXIT);
	cmd->path = NULL;
	if (cmd->full_cmd[0][0] != '/')
		cmd->path = get_path(mish, cmd->full_cmd[0]);
	hashmap_to_matrix(mish->env, &env, 0, 0);
	if (cmd->path == NULL)
		cmd->path = ft_strdup(cmd->full_cmd[0]);
	close_fds(mish, NULL);
	if (execve(cmd->path, cmd->full_cmd, env) != 0)
	{
		free(cmd->path);
		cmd->path = NULL;
		if (opendir(cmd->full_cmd[0]) != NULL)
			handle_exit(mish, cmd->full_cmd[0], IS_DIR, IS_EXIT);
		else if (cmd->full_cmd[0][0] == '/')
			handle_exit(mish, cmd->full_cmd[0], NO_FILE, IS_EXIT);
		else
			handle_exit(mish, cmd->full_cmd[0], CMD_NOT_FOUND, IS_EXIT);
	}
}

void	fork_cmds(t_data *mish, t_scmd *cmd, int pids[], int c)
{
	pids[c] = fork();
	config_signals_exec();
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

void	executor_loop(t_data *mish, int c)
{
	int		i;
	t_list	*curr;

	curr = mish->cmds;
	i = 0;
	while (curr && i < c)
	{
		signal(SIGINT, SIG_IGN);
		fork_cmds(mish, curr->content, mish->pids, i);
		curr = curr->next;
		i++;
	}
}

void	wait_loop(t_data *mish, int c)
{
	int		status;
	int		i;

	i = 0;
	while (i < c - 1)
	{
		waitpid(mish->pids[i], &status, 0);
		i++;
	}
	waitpid(mish->pids[i], &status, 0);
	if (WIFEXITED(status))
		mish->exit_status = WEXITSTATUS(status);
}

// Handles execution. If only one, built-in command,
// that is not `env`, no fork is done.
void	executor(t_data *mish)
{
	t_scmd	*first;
	int		fds[2];
	int		c;

	c = 0;
	if (!mish->cmds)
		return ;
	first = mish->cmds->content;
	if (mish->cmds->next == NULL && first->full_cmd != NULL
		&& check_if_builtin(first->full_cmd[0]) == 0
		&& ft_strncmp("env", first->full_cmd[0], 3) != 0)
	{
		builtins_router(mish, *first, NOT_EXIT);
		clean_executor(mish);
		return ;
	}
	set_file_descriptors(mish, fds, &c);
	mish->pids = malloc(sizeof(int) * c);
	if (!mish->pids)
		handle_exit(mish, "exec", FAILURE, NOT_EXIT);
	executor_loop(mish, c);
	wait_loop(mish, c);
	clean_executor(mish);
}
