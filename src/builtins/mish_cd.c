/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:20:56 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/08 11:43:23 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_dirs(t_data *mish, char **curr, char *pwd, int if_exit)
{
	struct stat	path_stat;

	if (stat(pwd, &path_stat) == 0 && (S_ISREG(path_stat.st_mode)) == 1)
	{
		handle_exit(mish, pwd, NOT_DIR, if_exit);
		return (CD_ERR);
	}
	if (chdir(pwd) != 0)
	{
		handle_exit(mish, pwd, CD_ERR, if_exit);
		return (CD_ERR);
	}
	*curr = getcwd(NULL, PATH_MAX);
	if (*curr == NULL)
	{
		handle_exit(mish, "cd: hashmap insert failed", CD_ERR, if_exit);
		return (CD_ERR);
	}
	return (SUCCESS);
}

// Changes  PWD and OLDPWD, deleting and freeing previous 
// versions.
static int	change_dir(t_data *mish, char *pwd, int if_exit)
{
	char	*curr;
	char	*old_pwd;

	if (get_dirs(mish, &curr, pwd, if_exit) == CD_ERR)
		return (CD_ERR);
	old_pwd = ft_strdup(hashmap_search(mish->env, "PWD"));
	search_and_delete(mish, "PWD");
	search_and_delete(mish, "OLDPWD");
	if (hashmap_insert("PWD", curr, mish->env, 0) == NULL
		|| hashmap_insert("OLDPWD", old_pwd, mish->env, 0) == NULL)
	{
		free(curr);
		free(old_pwd);
		handle_exit(mish, "cd: hashmap insert failed", CD_ERR, if_exit);
		return (CD_ERR);
	}
	free(old_pwd);
	free(curr);
	return (SUCCESS);
}

// Expands th '~' and cd with no arguments into home dir.
static int	expand_pwd(t_data *mish, char **pwd, char *arg, int if_exit)
{
	if (*pwd == NULL)
	{
		*pwd = hashmap_search(mish->env, "HOME");
		if (*pwd == NULL)
		{
			handle_exit(mish, "cd: HOME not set", CD_ERR, if_exit);
			return (CD_ERR);
		}
	}
	else if (ft_strncmp(arg, "-", 1) == 0)
	{
		*pwd = hashmap_search(mish->env, "OLDPWD");
		if (*pwd == NULL)
		{
			handle_exit(mish, "cd: OLDPWD not set", CD_ERR, if_exit);
			return (CD_ERR);
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

	if (cmd.full_cmd[1] && cmd.full_cmd[2] != NULL)
	{
		handle_exit(mish, "cd: too many arguments", CD_ERR, if_exit);
		return ;
	}
	pwd = cmd.full_cmd[1];
	if (expand_pwd(mish, &pwd, cmd.full_cmd[1], if_exit) == CD_ERR)
		return ;
	if (change_dir(mish, pwd, if_exit) == CD_ERR)
		return ;
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
