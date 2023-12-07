/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:00:19 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/12/07 18:57:12 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <dirent.h>

int	get_fd(int oldfd, char *path, int flags[2])
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		handle_exit(NULL, path, NO_FILE, NOT_EXIT);
	else if (!flags[0] && access(path, R_OK) == -1)
		handle_exit(NULL, path, NO_PERM, NOT_EXIT);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		handle_exit(NULL, path, NO_PERM, NOT_EXIT);
	else if (flags[0] && opendir(path) != NULL)
		handle_exit(NULL, path, IS_DIR, NOT_EXIT);
	if (flags[0] && flags[1])
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

static char	*get_heredoc_str(char *str[2], size_t len, char *limit, char *err)
{
	char	*tmp;

	str[0] = ft_calloc(sizeof(char), 1);
	str[1] = ft_calloc(sizeof(char), 1);
	while (g_exit_status != 130 && (!str[0] || ft_strncmp(str[0], limit, len)
			|| ft_strlen(limit) != len))
	{
		tmp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(tmp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", err, limit);
			break ;
		}
		tmp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(tmp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

int	get_heredoc_fd(char *limit)
{
	int		fd[2];
	char	*err;
	char	*str[2];

	str[0] = NULL;
	str[1] = NULL;
	g_exit_status = 0;
	err = "minishell: warning: here-document delimited by end-of-file";
	if (pipe(fd) == -1)
	{
		handle_exit(NULL, NULL, PIPE_ERR, NOT_EXIT);
		return (-1);
	}
	str[1] = get_heredoc_str(str, 0, limit, err);
	write(fd[WRITE_END], str[1], ft_strlen(str[1]));
	free(str[1]);
	close(fd[WRITE_END]);
	if (g_exit_status == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
