/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnavar <johnavar@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:45:19 by johnavar          #+#    #+#             */
/*   Updated: 2023/11/14 12:42:17 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	handle_exit(t_data *mish, int errno)
{
	if (mish)
		if (mish->env)
			hashmap_free_table(mish->env);
	exit(errno);
}
