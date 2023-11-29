/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:20:56 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/29 11:46:59 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	change_dir(t_data *mish, char *pwd, char *old_pwd, int if_exit)
{
	char	*curr;

	if (chdir(pwd) != 0)
	{
		handle_exit(mish, "mish: no such file or directory", FAILURE, if_exit);
		return (FAILURE);
	}
	if (hashmap_insert("OLDPWD", old_pwd, mish->env, 0) == NULL)
	{
		handle_exit(mish, "mish: cd: hashmap insert failed", FAILURE, if_exit);
		return (FAILURE);
	}
	curr = getcwd(NULL, PATH_MAX);
	if (curr == NULL)
	{
		handle_exit(mish, "mish: cd: hashmap insert failed", FAILURE, if_exit);
		return (FAILURE);
	}
	if (hashmap_insert("PWD", curr, mish->env, 0) == NULL)
	{
		handle_exit(mish, "mish: cd: hashmap insert failed", FAILURE, if_exit);
		return (FAILURE);
	}
	free(curr);
	return (SUCCESS);
}

static int	expand_pwd(t_data *mish, char **pwd, char *arg, int if_exit)
{
	if (*pwd == NULL)
	{
		*pwd = hashmap_search(mish->env, "HOME");
		if (*pwd == NULL)
		{
			handle_exit(mish, "mish: cd: HOME not set", FAILURE, if_exit);
			return (FAILURE);
		}
	}
	else if (ft_strncmp(arg, "-", 1) == 0)
	{
		*pwd = hashmap_search(mish->env, "OLDPWD");
		if (*pwd == NULL)
		{
			handle_exit(mish, "mish: cd: OLDPWD not set", FAILURE, if_exit);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

// Imitates Bash's cd function. If if_exit set to IS_EXIT (1),
// mish_cd will kill current process. NOT_EXIT used for when
// only one builtin command inputed
void	mish_cd(t_data *mish, t_scmd cmd, int if_exit)
{
	char	*pwd;
	char	*old_pwd;

	pwd = cmd.full_cmd[1];
	old_pwd = hashmap_search(mish->env, "PWD");
	if (expand_pwd(mish, &pwd, cmd.full_cmd[1], if_exit) == FAILURE)
		return ;
	if (change_dir(mish, pwd, old_pwd, if_exit) == FAILURE)
		return ;
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
