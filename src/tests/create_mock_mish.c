/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mock_mish.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:50:28 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/10 19:33:59 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern char	**environ; // temp way of getting enviroment variables

void	create_mock_mish(t_data *mish, char *line)
{
	printf("line is %s\n", line);
	char	**full_cmd;
	t_list	*cmd_list;
	t_scmd	*cmd;

	cmd_list = malloc(sizeof(t_scmd *) * 1);
	cmd = malloc(sizeof(t_scmd));
	full_cmd = ft_split(line, ' ');
	if (full_cmd == NULL)
	{
		ft_putstr_fd("Error creating fake cmd", STDERR_FILENO);
		exit(ERROR);
	}
	mish->pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(mish->pwd, PATH_MAX);
	cmd->in_fd = 0;
	cmd->out_fd = 1;
	cmd->full_cmd = full_cmd;
	cmd->path = get_cmd_path(cmd->full_cmd[0], environ); // TODO: replace environ
	cmd_list->content = cmd;
	cmd_list->next = NULL;
	mish->cmds = cmd_list;
}
