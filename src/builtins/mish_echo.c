/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:58:49 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/09 12:35:16 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// checks if the -n flag is used un any form, even
// incorrectly used like -nnnn. Returns 0 if str
// is not flag
static int	check_flag(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// Imitates Bash's echo function. If if_exit set to true (1),
// mish_cd will kill current process. False used for when
// only one builtin command inputed. Only -n flag accepted
void	mish_echo(t_data *mish, t_scmd cmd, int if_exit)
{
	int	i;
	int	f;

	i = 1;
	f = 0;
	while (cmd.full_cmd[i] != NULL)
	{
		if (check_flag(cmd.full_cmd[i]) == 0 || f == 1)
		{
			f = 1;
			ft_putstr_fd(cmd.full_cmd[i], cmd.out_fd);
			if (cmd.full_cmd[i + 1] != NULL)
				ft_putstr_fd(" ", cmd.out_fd);
		}
		i++;
	}
	if (check_flag(cmd.full_cmd[1]) == 0)
		ft_putstr_fd("\n", cmd.out_fd);
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
