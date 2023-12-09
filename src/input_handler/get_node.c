/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:45:06 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/12/09 11:45:08 by sebasnadu        ###   ########.fr       */
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

static void	get_node_err(char **cmds[2], int *i, t_data *mish)
{
	if (cmds[1][*i] && cmds[1][*i][0] == '|')
		handle_exit(mish, "`||'", SYNTAX_ERR, NOT_EXIT);
	else
		handle_exit(mish, "`|'", SYNTAX_ERR, NOT_EXIT);
	*i = -2;
}

t_scmd	*get_node(t_scmd *node, char **cmds[2], int *i, t_data *mish)
{
	if (cmds[1][*i] && !(*i == 1 && cmds[1][*i - 1][0] == '|'))
	{
		if (cmds[1][*i][0] == '>' && cmds[1][*i + 1]
			&& cmds[1][*i + 1][0] == '>')
			node = redir_out_append(node, cmds, i, mish);
		else if (cmds[1][*i][0] == '>')
			node = redir_out(node, cmds, i, mish);
		else if (cmds[1][*i][0] == '<' && cmds[1][*i + 1]
			&& cmds[1][*i + 1][0] == '<')
			node = redir_in_heredoc(node, cmds, i, mish);
		else if (cmds[1][*i][0] == '<')
			node = redir_in(node, cmds, i, mish);
		else if (cmds[1][*i][0] != '|' || (cmds[1][*i][0] == '|'
				&& cmds[1][*i][1] == 0))
			node->full_cmd = push_token(node->full_cmd, cmds[0][*i], -1);
		else
			get_node_err(cmds, i, mish);
		return (node);
	}
	get_node_err(cmds, i, mish);
	return (node);
}
