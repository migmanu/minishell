/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:20:56 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/16 20:06:38 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mish_cd(t_data *mish, t_scmd cmd)
{
	mish->old_pwd = hashmap_search(mish->env, "PWD");
	if (mish->old_pwd == NULL)
	{
		g_exit_status = ERROR;
		return ;
	}
	hashmap_insert("PWD", cmd.full_cmd[1], mish->env);
	g_exit_status = SUCCESS;
}
