/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_promt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:43:12 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/21 12:30:18 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**hashmap_to_matrix(t_hashmap *env, char ***matrix, unsigned int i,
				unsigned int j)
{
	char			*tmp_str;
	char			*tmp_str2;
	t_hash_item		*current;
	t_hash_item		*tmp;

	*matrix = (char **)malloc(sizeof(char *) * (env->size + 1));
	while (i < env->size)
	{
		current = env->items[i];
		while (current != NULL)
		{
			tmp = current->next;
			tmp_str = ft_strdup(current->key);
			tmp_str2 = ft_strjoin(tmp_str, "=");
			free(tmp_str);
			tmp_str = ft_strjoin(tmp_str2, current->value);
			free(tmp_str2);
			(*matrix)[j] = tmp_str;
			current = tmp;
			j++;
		}
		i++;
	}
	(*matrix)[j] = NULL;
	return (*matrix);
}

char	**get_output(int fd, char ***var)
{
	char	*line;
	char	*tmp;
	char	*tmp_matrix;

	line = NULL;
	tmp = NULL;
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
	return (*matrix);
}

char	**exec(char	***var, char *path, char *cmd, char **env)
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
	return (*var);
}

char	*get_user(t_data *mish)
{
	char	**user;
	char	*tmp;
	char	*tmp2;
	char	**env;

	env = hashmap_to_matrix(mish->env, &env, 0, 0);
	user = exec(&user, "/usr/bin/whoami", "whoami", env);
	if (!user)
		user = ft_extend_matrix(user' "guest");
	if (!ft_strncmp(user[0], "root", 4))
		tmp = ft_strjoin(NULL, RED);
	else
		tmp = ft_strjoin(NULL, GREEN);
	tmp2 = ft_strjoin(tmp, user[0]);
	free(tmp);
	ft_matrixfree(&user);
	return (tmp2);
}

char	*get_cd(t_data *mish)
{
	char	*home;
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, );
	if (!pwd)
		pwd = ft_strdup("/");
	home = hashmap_search(mish->env, "HOME");
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		tmp = pwd;
		pwd = ft_strjoin("~", &pwd[ft_strlen(home)]);
		free(tmp);
	}
	free(home);
	home = ft_strjoin(GRAY, pwd);
	free(pwd);
	pwd = ft_strjoin(home, " ");
	free(home);
	home = ft_strjoin(" ", pwd);
	free(pwd);
	pwd = ft_strjoin(home, DEFAULT);
	free(home);
	return (pwd);
}

char	*create_prompt(t_data *mish)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = get_user(mish);
	tmp2 = ft_strjoin(tmp, "@mish󰄛")
	free(tmp);
	tmp3 = get_cd(mish);
	tmp = ft_strjoin(tmp2, tmp3);
	free(tmp2);
	free(tmp3);
	if (g_exit_status == 0)
		tmp2 = ft_strjoin(tmp, GREEN);
	else
		tmp2 = ft_strjoin(tmp, RED);
	free(tmp);
	tmp = ft_strjoin(tmp2, "$> ");
	free(tmp2);
	tmp2 = ft_strjoin(tmp, DEFAULT);	
	free(tmp);
	return (tmp2);
}

char	*init_prompt(t_data *mish)
{
	char	*prompt;
	char	*line;

	prompt = create_prompt(mish);
	line = readline(prompt);
	free(prompt);
	if (line)
		add_history(line);
	else
		exit(SUCCESS);
	return (line);
}
