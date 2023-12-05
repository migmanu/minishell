/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:28:11 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/05 15:24:12 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Checks all chars are alpha or =
int	check_key(const char *key)
{
	int	i;

	i = 0;
	if (key[0] == '\0' || key[0] == '=')
		return (0);
	while (key[i] != '\0' && key[i] != '=')
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '=')
			return (0);
		if (key[i] == '=' && ft_isalnum(key[i - 1]) == 0 && key[i + 1] != '\0')
			return (0);
		i++;
	}
	return (1);
}

static int	unset_loop(t_data *mish, t_scmd cmd, int *c)
{
	while (cmd.full_cmd[++(c[0])] != NULL)
	{
		if (hashmap_search(mish->env, cmd.full_cmd[c[0]]) != NULL)
		{
			if (check_key(cmd.full_cmd[c[0]]) == 0)
			{
				ft_putstr_fd("mish: unset: ", STDERR_FILENO);
				ft_putstr_fd(cmd.full_cmd[c[0]], STDERR_FILENO);
				ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
				c[1] = FAILURE;
			}
			else if (hashmap_delete(mish->env, cmd.full_cmd[c[0]]) != 0)
			{
				ft_putstr_fd("mish: unset: ", STDERR_FILENO);
				ft_putstr_fd(cmd.full_cmd[c[0]], STDERR_FILENO);
				ft_putstr_fd(" error deleting var\n", STDERR_FILENO);
				c[1] = FAILURE;
			}
		}
	}
	return (c[1]);
}

void	mish_unset(t_data *mish, t_scmd cmd, int if_exit)
{
	int	c[2];

	c[0] = -1;
	c[1] = 0;
	if (cmd.full_cmd[1] == NULL)
		handle_exit(mish, NULL, SUCCESS, if_exit);
	unset_loop(mish, cmd, c);
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
