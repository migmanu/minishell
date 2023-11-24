/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:20:56 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/24 13:43:55 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// imitates Bash's cd function. If if_exit set to true (1),
// mish_cd will kill current process. False used for when
// only one builtin command inputed
void	mish_cd(t_data *mish, t_scmd cmd, int if_exit)
{
	char	*pwd;
	char	*old_pwd;

	pwd = cmd.full_cmd[1];
	old_pwd = hashmap_search(mish->env, "PWD");
	if (pwd == NULL)
	{
		pwd = hashmap_search(mish->env, "HOME");
	}
	else if (ft_strncmp(cmd.full_cmd[1], "-", 1) == 0)
	{
		pwd = hashmap_search(mish->env, "OLDPWD");
	}
	if (chdir(pwd) != 0)
	{
		handle_exit(mish, "mish : no such file or directory", FAILURE, if_exit);
		return ;
	}
	hashmap_insert("OLDPWD", old_pwd, mish->env, 0); // TODO: error handling
	hashmap_insert("PWD", getcwd(NULL, PATH_MAX), mish->env, 0);
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
