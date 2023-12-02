/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:28:11 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/02 17:15:19 by jmigoya-         ###   ########.fr       */
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
		if (hashmap_search(mish->env, cmd.full_cmd[i]) == NULL)
		{
			i++;
			continue ;
		}
		if (hashmap_delete(mish->env, cmd.full_cmd[i]) == 0)
		{
			handle_exit(mish, "mish: unset: error deleting var", \
			FAILURE, if_exit);
			continue ;
		}
		i++;
	}
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
