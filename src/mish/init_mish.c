/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:33:52 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/23 20:44:24 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	get_sh_pid(t_data *mish)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		handle_exit(mish, NULL, FORK_ERR, IS_EXIT);
	if (pid == 0)
		handle_exit(mish, NULL, FAILURE, IS_EXIT);
	waitpid(pid, NULL, 0);
	mish->pid = pid - 1;
}

static t_data	*check_env(t_data *mish, char *argv[])
{
	char	*tmp;
	int		nbr;

	nbr = 1;
	if (!hashmap_search(mish->env, "PWD"))
	{
		tmp = getcwd(NULL, 0);
		hashmap_insert("PWD", tmp, mish->env);
		free(tmp);
	}
	tmp = hashmap_search(mish->env, "SHLVL");
	if (tmp && ft_atoi(tmp) > 0)
		nbr = ft_atoi(tmp) + 1;
	tmp = ft_itoa(nbr);
	hashmap_insert("SHLVL", tmp, mish->env);
	free(tmp);
	if (!hashmap_search(mish->env, "PATH"))
		hashmap_insert("PATH", "/usr/local/sbin:/usr/local/bin:/usr/bin:/bin",
			mish->env);
	if (!hashmap_search(mish->env, "_"))
		hashmap_insert("_", argv[0], mish->env);
	return (mish);
}

void	init_mish(t_data *mish, char *argv[], char *envp[])
{
	g_exit_status = 0;
	mish->cmds = NULL;
	mish->env = env_to_hash(envp);
	mish->pids = NULL;
	check_env(mish, argv);
	get_sh_pid(mish);
}
