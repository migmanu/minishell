/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:13:15 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/12/06 12:41:48 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_history(t_data *mish, int i)
{
	while (mish->history[i])
	{
		printf("  %d:  %s\n", i + 1, mish->history[i]);
		i++;
	}
}

static int	is_nbr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

// Prints the command history. If if_exit set to true, exits
// the process. False is generally used for cases of single
// builtin commands that require no fork.
void	mish_history(t_data *mish, t_scmd cmd, int if_exit)
{
	int	len;
	int	index;

	len = ft_matrixlen(mish->history);
	index = 0;
	if (cmd.full_cmd[1] == NULL)
		print_history(mish, index);
	else if (!is_nbr(cmd.full_cmd[1]))
	{
		handle_exit(mish, cmd.full_cmd[1], HIS_WRONG_ARG, if_exit);
		return ;
	}
	else if (cmd.full_cmd[1] && !cmd.full_cmd[2])
	{
		index = len - ft_atoi(cmd.full_cmd[1]);
		if (index < 0)
			index = 0;
		print_history(mish, index);
	}
	else if (cmd.full_cmd[1] && cmd.full_cmd[2])
	{
		handle_exit(mish, NULL, HIS_WRONG_ARGS, if_exit);
		return ;
	}
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
