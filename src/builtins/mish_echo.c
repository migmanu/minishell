/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:58:49 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/20 19:54:19 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_flag(char *str)
{
	int	i;

	if (!str)
		return (-1);
	if (str[0] != '-' || str[1] != 'n')
		return (1);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	mish_echo(t_data *mish, t_scmd cmd, int if_exit)
{
	int	i;

	printf("echo init, out %d\n", cmd.out_fd);
	i = 1;
	while (cmd.full_cmd[i] != NULL)
	{
		if (check_flag(cmd.full_cmd[i]) != 0)
		{
			ft_putstr_fd(cmd.full_cmd[i], cmd.out_fd);
			if (cmd.full_cmd[i + 1] != NULL)
				ft_putstr_fd(" ", cmd.out_fd);
		}
		i++;
	}
	if (check_flag(cmd.full_cmd[1]) != 0)
		ft_putstr_fd("\n", cmd.out_fd);
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
