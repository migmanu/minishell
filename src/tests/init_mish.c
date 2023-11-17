/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:33:52 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/17 19:30:40 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char	**environ; // temp way of getting enviroment variables

static void	get_sh_pid(t_data *mish)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		mish_error(mish, NULL, FORK_ERR, 1);
	if (pid == 0)
		mish_error(mish, NULL, FAILURE, 1);
	waitpid(pid, NULL, 0);
	mish->pid = pid - 1;
}

t_data	*check_env(t_data *mish)
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
	hashmap_insert("SHLVL", ft_itoa(nbr), mish->env);
	return (NULL);
}

// TODO: Handling not envp
void	init_mish(t_data *mish, char *envp[])
{
	mish->cmds = NULL;
	mish->env = env_to_hash(envp);
	check_env(mish);
	get_sh_pid(mish);
	hashmap_print_table(mish->env);
}
