/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnavar <johnavar@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:36:20 by johnavar          #+#    #+#             */
/*   Updated: 2023/12/07 20:29:19 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Wrapper for the hashmap_delete function.
void	search_and_delete(t_data *mish, char *key)
{
	if (hashmap_search_key(mish->env, key) == NULL)
		return ;
	if (hashmap_delete(mish->env, key) == FAILURE)
	{
		ft_putstr_fd("mish: ", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd(" hashmap_delete error\n", STDERR_FILENO);
		return ;
	}
}

char	*ft_strjoin_var(unsigned int arg_size, ...)
{
	unsigned int	i;
	va_list			arg_lst;
	char			*arg_buff;
	char			*tmp;
	char			*new;

	va_start(arg_lst, arg_size);
	i = 0;
	new = NULL;
	while (i < arg_size)
	{
		arg_buff = va_arg(arg_lst, char *);
		if (new == NULL)
			new = ft_strdup(arg_buff);
		else
		{
			tmp = ft_strjoin(new, arg_buff);
			free(new);
			new = tmp;
		}
		i++;
	}
	va_end(arg_lst);
	return (new);
}

char	**hashmap_to_matrix(t_hashmap *env, char ***matrix, unsigned int i,
				unsigned int j)
{
	char			*tmp_str;
	t_hash_item		*current;
	t_hash_item		*tmp;

	*matrix = ft_calloc(env->count + 1, sizeof(char *));
	if (!*matrix)
		return (NULL);
	while (i < env->size)
	{
		current = env->items[i];
		while (current != NULL)
		{
			tmp = current->next;
			tmp_str = ft_strjoin_var(3, current->key, "=", current->value);
			(*matrix)[j] = tmp_str;
			current = tmp;
			j++;
		}
		i++;
	}
	return (*matrix);
}

static void	get_output(int fd, char ***matrix)
{
	char	*line;
	char	*tmp;
	char	**tmp_matrix;

	line = NULL;
	tmp = NULL;
	tmp_matrix = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = ft_strtrim(line, "\n");
		free(line);
		tmp_matrix = ft_extend_matrix(tmp_matrix, tmp);
		free(tmp);
	}
	ft_matrixfree(matrix);
	*matrix = tmp_matrix;
}

void	exec(char	***var, char *path, char *cmd, char **env)
{
	pid_t	pid;
	int		fd[2];
	char	**tmp;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[READ_END]);
		tmp = ft_split(cmd, ' ');
		dup2(fd[WRITE_END], STDOUT_FILENO);
		close(fd[WRITE_END]);
		if (access(path, F_OK) == 0)
			execve(path, tmp, env);
		exit(FAILURE);
	}
	close(fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	get_output(fd[READ_END], var);
	close(fd[READ_END]);
}
