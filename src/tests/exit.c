/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnavar <johnavar@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:45:19 by johnavar          #+#    #+#             */
/*   Updated: 2023/11/14 12:22:24 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

void	free_mish(t_data *mish)
{
	if (mish->env)
		hashmap_free_table(mish->env);
	if (mish->old_pwd)
	{
		free(mish->old_pwd);
		mish->old_pwd = NULL;
	}
}

// TODO: the exit code its wrong, maybe we can implement a global with
// the las exit and use here to exit correct.
void	mish_error(t_data *mish, char *param, int err, int is_exit)
{
	if (err != SUCCESS && err != FAILURE)
	{
		ft_putstr_fd("mish: ", STDERR_FILENO);
		if (err == INV_ARGS)
			ft_putstr_fd("No arguments needed: ", STDERR_FILENO);
		else if (err == FORK_ERR)
			perror("fork");
		else if (err == UNQUOTE)
			ft_putstr_fd("Unmatch quote", STDERR_FILENO);
		if (param)
			ft_putstr_fd(param, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (mish)
		if (mish->env)
			hashmap_free_table(mish->env);
	if (is_exit && err != FORK_ERR)
		exit(err);
	else
		exit(errno);
}
