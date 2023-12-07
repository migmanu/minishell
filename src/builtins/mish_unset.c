/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:28:11 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/06 21:29:14 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Checks all chars are alpha or '='. 'i' must be set
// to -1 in all cases and exp must be set to 1 if
// no numbers are allowed before alphabetical chars.
int	check_key(const char *key, int i, int exp)
{
	if (key[0] == '\0' || key[0] == '=')
		return (0);
	if (exp == 1)
	{
		while (key[++i] != '\0')
		{
			if (ft_isalpha(key[i]) == 0)
				return (0);
			else
				break ;
		}
	}
	i = -1;
	while (key[++i] != '\0' && key[i] != '=')
	{
		if (ft_isalnum(key[i]) == 0 && key[i] != '=')
			return (0);
		if (key[i] == '=' && ft_isalnum(key[i - 1]) == 0 && key[i + 1] != '\0')
			return (0);
	}
	return (1);
}

static int	unset_loop(t_data *mish, t_scmd cmd, int *c)
{
	while (cmd.full_cmd[++(c[0])] != NULL)
	{
		if (hashmap_search(mish->env, cmd.full_cmd[c[0]]) != NULL)
		{
			if (check_key(cmd.full_cmd[c[0]], -1, 0) == 0)
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

// Imitates Bash's unset function. If if_exit set to IS_EXIT (1),
// mish_cd will kill current process. NOT_EXIT used for when
// only one builtin command inputed. Unset has less syntax
// requirements than export.
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
