/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:25:19 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/16 20:04:35 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mish_pwd(t_data *mish, t_scmd cmd)
{
	printf("mish_pwd init\n");
	char	*str;

	str = hashmap_search(mish->env, "PWD");
	if (str == NULL)
	{
		g_exit_status = ERROR;
		return ;
	}
	ft_putstr_fd(str, cmd.out_fd);
	ft_putstr_fd("\n", cmd.out_fd);
	g_exit_status = SUCCESS;
}
