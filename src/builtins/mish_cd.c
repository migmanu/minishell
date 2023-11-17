/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:20:56 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/17 18:06:11 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

void	mish_cd(t_data *mish, t_scmd cmd)
{
	char	*pwd;
	char	*old_pwd;

	pwd = hashmap_search(mish->env, "PWD");
	old_pwd = hashmap_search(mish->env, "OLD_PWD");
	if (!pwd || !old_pwd)
	{
		mish_error(mish, NULL, SUCCESS, 0);
	}
	if (ft_strncmp(cmd.full_cmd[1], "-", 1) == 0)
	{
		hashmap_insert("PWD", old_pwd, mish->env); // TODO: error handling
		mish_error(mish, NULL, SUCCESS, 1);
	}
	hashmap_insert("OLD_PWD", pwd, mish->env); // TODO: error handling
	if (chdir(cmd.full_cmd[1]) != 0)
	{
		mish_error(mish, cmd.full_cmd[1], NO_FILE, 0);
	}
	hashmap_insert("PWD", cmd.full_cmd[1], mish->env); // TODO: error handling
	mish_error(mish, NULL, SUCCESS, 0);
}
