/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:57:07 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/12/01 16:57:06 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_scmd	*redir_out_append(t_scmd *node, char **cmds, int *i)
{
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	(*i)++;
	if (cmds[++(*i)] && cmds[*i][0] != '>')
		node->out_fd = get_fd(node->out_fd, cmds[*i], flags);
	if (!cmds[*i] || cmds[*i][0] == '>' || node->out_fd == -1)
	{
		if (cmds[*i] && cmds[*i][0] == '>')
			handle_exit(NULL, "`>>'", SYNTAX_ERR, NOT_EXIT);
		else if (node->out_fd != -1)
			handle_exit(NULL, "`newline'", SYNTAX_ERR, NOT_EXIT);
		*i = -1;
	}
	return (node);
}

t_scmd	*redir_out(t_scmd *node, char **cmds, int *i)
{
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	(*i)++;
	if (cmds[*i] && cmds[*i][0] != '<')
		node->out_fd = get_fd(node->out_fd, cmds[*i], flags);
	if (!cmds[*i] || cmds[*i][0] == '<' || node->out_fd == -1)
	{
		if (cmds[*i] && cmds[*i][0] == '<')
			handle_exit(NULL, "`<'", SYNTAX_ERR, NOT_EXIT);
		else if (node->out_fd != -1)
			handle_exit(NULL, "`newline'", SYNTAX_ERR, NOT_EXIT);
		else
			g_exit_status = 1;
		*i = -1;
	}
	return (node);
}

t_scmd	*redir_in_heredoc(t_scmd *node, char **cmds, int *i)
{
	char	*limit;

	limit = NULL;
	(*i)++;
	if (cmds[++(*i)] && cmds[*i][0] != '<')
	{
		limit = cmds[*i];
		node->in_fd = get_heredoc_fd(limit);
	}
	if (!cmds[*i] || cmds[*i][0] == '<' || node->in_fd == -1)
	{
		if (cmds[*i] && cmds[*i][0] == '<')
			handle_exit(NULL, "`<<'", SYNTAX_ERR, NOT_EXIT);
		else if (node->in_fd != -1)
			handle_exit(NULL, "`newline'", SYNTAX_ERR, NOT_EXIT);
		*i = -1;
	}
	return (node);
}

t_scmd	*redir_in(t_scmd *node, char **cmds, int *i)
{
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	(*i)++;
	if (cmds[*i] && cmds[*i][0] != '>')
		node->in_fd = get_fd(node->in_fd, cmds[*i], flags);
	if (!cmds[*i] || cmds[*i][0] == '>' || node->in_fd == -1)
	{
		if (node->in_fd != -1 || (cmds[*i] && cmds[*i][0] == '>'))
			handle_exit(NULL, "`newline'", SYNTAX_ERR, NOT_EXIT);
		else
			g_exit_status = 1;
		*i = -1;
	}
	return (node);
}
