/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:20:56 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/20 17:27:51 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

// imitates Bash's cd function. If if_exit set to true (1),
// mish_cd will kill current process. False used for when
// only one builtin command inputed
void	mish_cd(t_data *mish, t_scmd cmd, int if_exit)
{
	char	*pwd;
	char	*old_pwd;

	printf("cd init, dest %s\n", cmd.full_cmd[1]);
	pwd = hashmap_search(mish->env, "PWD");
	old_pwd = hashmap_search(mish->env, "OLD_PWD");
	if (!pwd || !old_pwd)
	{
		handle_exit(mish, NULL, SUCCESS, if_exit);
		return ;
	}
	if (ft_strncmp(cmd.full_cmd[1], "-", 1) == 0)
	{
		hashmap_insert("PWD", old_pwd, mish->env); // TODO: error handling
		handle_exit(mish, NULL, SUCCESS, if_exit);
		return ;
	}
	hashmap_insert("OLD_PWD", pwd, mish->env); // TODO: error handling
	if (chdir(cmd.full_cmd[1]) != 0)
	{
		handle_exit(mish, cmd.full_cmd[1], NO_FILE, if_exit);
		return ;
	}
	hashmap_insert("PWD", cmd.full_cmd[1], mish->env); // TODO: error handling
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
