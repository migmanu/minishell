/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:28:11 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/25 18:37:04 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mish_unset(t_data *mish, t_scmd cmd, int if_exit)
{
	int	i;

	i = 1;
	if (cmd.full_cmd[1] == NULL)
		handle_exit(mish, NULL, SUCCESS, if_exit);
	while (cmd.full_cmd[i] != NULL)
	{
		hashmap_delete(mish->env, cmd.full_cmd[i]); // TODO: error check
		i++;
	}
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
