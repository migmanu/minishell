/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:45:06 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/15 17:59:37 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**push_token(char **cmds, char *token, int i)
{
	char	**new;

	if (!token)
		return (cmds);
	new = malloc((ft_matrixlen(cmds) + 2) * sizeof(char *));
	if (!new)
		return (cmds);
	while (++i < ft_matrixlen(cmds))
	{
		new[i] = ft_strdup(cmds[i]);
		if (!new[i])
		{
			ft_matrixfree(&new);
			return (cmds);
		}
	}
	new[i] = ft_strdup(token);
	if (!new[i])
	{
		ft_matrixfree(&new);
		return (cmds);
	}
	new[i + 1] = NULL;
	ft_matrixfree(&cmds);
	return (new);
}

t_scmd	*get_node(t_scmd *node, char **cmds[2], int *i)
{
	if (cmds[1][*i])
	{
		if (cmds[1][*i][0] == '>' && cmds[1][*i + 1]
			&& cmds[1][*i + 1][0] == '>')
			node = redir_out_append(node, cmds[0], i);
		else if (cmds[1][*i][0] == '>')
			node = redir_out(node, cmds[0], i);
		else if (cmds[1][*i][0] == '<' && cmds[1][*i + 1]
			&& cmds[1][*i + 1][0] == '<')
			node = redir_in_heredoc(node, cmds[0], i);
		else if (cmds[1][*i][0] == '<')
			node = redir_in(node, cmds[0], i);
		else if (cmds[1][*i][0] != '|')
			node->full_cmd = push_token(node->full_cmd, cmds[0][*i], -1);
		else
		{
			mish_error(NULL, NULL, PIPE_ERR, 0);
			*i = -2;
		}
		return (node);
	}
	mish_error(NULL, NULL, PIPE_ERR, 0);
	*i = -2;
	return (node);
}
