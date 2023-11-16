/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:57:07 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/15 18:23:25 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_scmd	*redir_out_append(t_scmd *node, char **cmds, int *i)
{
	char	*err;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	err = "mish: syntax error near unexpected token `newline'";
	(*i)++;
	if (cmds[++(*i)])
		node->out_fd = get_fd(node->out_fd, cmds[*i], flags);
	if (!cmds[*i] || node->out_fd == -1)
	{
		*i = -1;
		if (node->out_fd != -1)
		{
			ft_putstr_fd(err, STDERR_FILENO);
			g_exit_status = 2;
		}
	}
	return (node);
}

t_scmd	*redir_out(t_scmd *node, char **cmds, int *i)
{
	char	*err;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	err = "mish: syntax error near unexpected token `newline'";
	(*i)++;
	if (cmds[*i])
		node->out_fd = get_fd(node->out_fd, cmds[*i], flags);
	if (!cmds[*i] || node->out_fd == -1)
	{
		*i = -1;
		if (node->out_fd != -1)
		{
			ft_putstr_fd(err, STDERR_FILENO);
			g_exit_status = 2;
		}
		else
			g_exit_status = 1;
	}
	return (node);
}

t_scmd	*redir_in_heredoc(t_scmd *node, char **cmds, int *i)
{
	char	*err;
	char	*limit;

	limit = NULL;
	err = "mish: syntax error near unexpected token `newline'";
	(*i)++;
	if (cmds[++(*i)])
	{
		limit = cmds[*i];
		node->in_fd = get_heredoc_fd(limit);
	}
	if (!cmds[*i] || node->in_fd == -1)
	{
		*i = -1;
		if (node->in_fd != -1)
		{
			ft_putstr_fd(err, STDERR_FILENO);
			g_exit_status = 2;
		}
	}
	return (node);
}

t_scmd	*redir_in(t_scmd *node, char **cmds, int *i)
{
	char	*err;
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	err = "mish: syntax error near unexpected token `newline'";
	(*i)++;
	if (cmds[*i])
		node->in_fd = get_fd(node->in_fd, cmds[*i], flags);
	if (!cmds[*i] || node->in_fd == -1)
	{
		*i = -1;
		if (node->in_fd != -1)
		{
			ft_putstr_fd(err, STDERR_FILENO);
			g_exit_status = 2;
		}
		else
			g_exit_status = 1;
	}
	return (node);
}
