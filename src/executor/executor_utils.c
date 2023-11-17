/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:08:05 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/17 20:26:33 by jmigoya-         ###   ########.fr       */
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

void	dup_s_cmds(t_scmd *cmd)
{
	printf("dup_s_cmds init, cmd: %s in: %d | out: %d\n", cmd->full_cmd[0], \
	cmd->in_fd, cmd->out_fd);
	if (cmd->out_fd != STDOUT_FILENO)
	{
		printf("duping out, %d for %d\n", STDOUT_FILENO, cmd->out_fd);
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
	if (cmd->in_fd != STDIN_FILENO)
	{
		printf("duping in\n");
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
	printf("end dup\n");
}
