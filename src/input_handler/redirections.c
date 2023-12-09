/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:57:07 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/12/09 12:29:26 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_scmd	*redir_out_append(t_scmd *node, char **cmds[2], int *i, t_data *mish)
{
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	(*i)++;
	if (cmds[0][++(*i)] && cmds[1][*i] && cmds[1][*i][0] != '<'
		&& cmds[1][*i][0] != '>' && cmds[1][*i][0] != '|')
		node->out_fd = get_fd(node->out_fd, cmds[0][*i], flags, mish);
	if (node->out_fd == -1 || !cmds[0][*i] || !cmds[1][*i] \
	|| cmds[1][*i][0] == '>' || cmds[1][*i][0] == '|' || cmds[1][*i][0] == '<')
	{
		if (cmds[1][*i] && cmds[1][*i + 1] && cmds[1][*i][0] == '>'
			&& cmds[1][*i + 1][0] == '>')
			handle_exit(mish, "`>>'", SYNTAX_ERR, NOT_EXIT);
		else if (cmds[1][*i] && cmds[1][*i][0] == '>')
			handle_exit(mish, "`>'", SYNTAX_ERR, NOT_EXIT);
		else if (cmds[1][*i] && cmds[1][*i][0] == '<')
			handle_exit(mish, "`<'", SYNTAX_ERR, NOT_EXIT);
		else if (cmds[1][*i] && cmds[1][*i][0] == '|')
			handle_exit(mish, "`|'", SYNTAX_ERR, NOT_EXIT);
		else if (node->out_fd != -1)
			handle_exit(mish, "`newline'", SYNTAX_ERR, NOT_EXIT);
		*i = -1;
	}
	return (node);
}

t_scmd	*redir_out(t_scmd *node, char **cmds[2], int *i, t_data *mish)
{
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	(*i)++;
	if (cmds[0][*i] && cmds[1][*i] && (cmds[1][*i][0] != '<'
		&& cmds[1][*i][0] != '>' && cmds[1][*i][0] != '|'))
		node->out_fd = get_fd(node->out_fd, cmds[0][*i], flags, mish);
	if (node->out_fd == -1 || !cmds[0][*i] || !cmds[1][*i] \
	|| cmds[1][*i][0] == '<' || cmds[1][*i][0] == '|' || cmds[1][*i][0] == '>')
	{
		if (cmds[1][*i] && cmds[1][*i][0] == '<')
			handle_exit(mish, "`<'", SYNTAX_ERR, NOT_EXIT);
		else if (node->out_fd != -1 || (cmds[1][*i] && cmds[1][*i][0] == '|'))
			handle_exit(mish, "`newline'", SYNTAX_ERR, NOT_EXIT);
		else
			mish->exit_status = 1;
		*i = -1;
	}
	return (node);
}

static void	heredoc_perror(char **cmds, int *i, t_data *mish, t_scmd *node)
{
	int	len;

	len = 0;
	while (cmds[*i] && cmds[*i][0] == '<')
	{
		(*i)++;
		len++;
	}
	if (len == 2)
		handle_exit(mish, "`<'", SYNTAX_ERR, NOT_EXIT);
	else if (len == 3)
		handle_exit(mish, "`<<'", SYNTAX_ERR, NOT_EXIT);
	else if (len == 4)
		handle_exit(mish, "`<<<'", SYNTAX_ERR, NOT_EXIT);
	else if (cmds[*i] && cmds[*i][0] == '>')
		handle_exit(mish, "`>'", SYNTAX_ERR, NOT_EXIT);
	else if (cmds[*i] && cmds[*i][0] == '|')
		handle_exit(mish, "`|'", SYNTAX_ERR, NOT_EXIT);
	else if (node->in_fd != -1 || len == 1)
		handle_exit(mish, "`newline'", SYNTAX_ERR, NOT_EXIT);
	else
		mish->exit_status = 1;
}

t_scmd	*redir_in_heredoc(t_scmd *node, char **cmds[2], int *i, t_data *mish)
{
	char	*limit;

	limit = NULL;
	(*i)++;
	if (cmds[0][++(*i)] && (cmds[1][*i][0] != '<' && cmds[1][*i][0] != '>'
		&& cmds[1][*i][0] != '|'))
	{
		limit = cmds[0][*i];
		node->in_fd = get_heredoc_fd(limit, mish);
	}
	if (!cmds[0][*i] || node->in_fd == -1 || (cmds[1][*i][0] == '<'
			|| cmds[1][*i][0] == '|' || cmds[1][*i][0] == '>'))
	{
		heredoc_perror(cmds[1], i, mish, node);
		*i = -1;
	}
	return (node);
}

t_scmd	*redir_in(t_scmd *node, char **cmds[2], int *i, t_data *mish)
{
	int		flags[2];

	flags[0] = 0;
	flags[1] = 0;
	(*i)++;
	if (cmds[0][*i] && (access(cmds[0][*i], F_OK) == 0 || (cmds[1][*i][0] != '<'
			&& cmds[1][*i][0] != '>' && cmds[1][*i][0] != '|')))
		node->in_fd = get_fd(node->in_fd, cmds[0][*i], flags, mish);
	if (!cmds[0][*i] || node->in_fd == -1 || access(cmds[0][*i], F_OK) == -1
	|| cmds[1][*i][0] == '>' || cmds[1][*i][0] == '<' || cmds[1][*i][0] == '|')
	{
		if (node->in_fd != -1 || (cmds[0][*i] && cmds[1][*i]
			&& (cmds[1][*i][0] == '<' || cmds[1][*i][0] == '|'
			|| cmds[1][*i][0] == '>')))
			handle_exit(mish, "`newline'", SYNTAX_ERR, NOT_EXIT);
		else
			mish->exit_status = 1;
		*i = -1;
	}
	return (node);
}
