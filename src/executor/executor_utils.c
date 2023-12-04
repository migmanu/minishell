/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:08:05 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/04 09:50:00 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(t_data *mish, char *cmd)
{
	char	**path_vec;
	char	*tmp_path;
	char	*path;
	int		i;

	i = 0;
	path_vec = ft_split(hashmap_search(mish->env, "PATH") + 5, ':');
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

void	dup_cmd(t_scmd *cmd)
{
	if (cmd->out_fd != STDOUT_FILENO)
	{
		dup2(cmd->out_fd, STDOUT_FILENO);
	}
	if (cmd->in_fd != STDIN_FILENO)
	{
		dup2(cmd->in_fd, STDIN_FILENO);
	}
}

// If pipes are present, modifies the fd_in and fd_out of each
// command, except the fd_in of the first and the fd_out of
// the last one. Those need to be set before. C ends up as a
// count of all commands to execute.
void	set_file_descriptors(t_data *mish, int fds[2], int *c)
{
	t_scmd	*cmd;
	t_list	*curr;
	t_scmd	*next_cmd;

	curr = mish->cmds;
	while (curr)
	{
		(*c)++;
		cmd = curr->content;
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
		curr = curr->next;
	}
}
