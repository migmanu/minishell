/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnavar <johnavar@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:45:19 by johnavar          #+#    #+#             */
/*   Updated: 2023/12/08 16:47:51 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fds(t_data *mish, t_scmd *cmd)
{
	t_scmd	*node;
	t_list	*curr;

	curr = mish->cmds;
	while (curr != NULL)
	{
		node = curr->content;
		if (node == cmd)
		{
			curr = curr->next;
			continue ;
		}
		if (node->in_fd != STDIN_FILENO)
			close(node->in_fd);
		if (node->out_fd != STDOUT_FILENO)
			close(node->out_fd);
		curr = curr->next;
	}
}

void	free_scmd(void *content)
{
	t_scmd	*node;

	node = content;
	ft_matrixfree(&node->full_cmd);
	free(node->full_cmd);
	if (node->in_fd != STDIN_FILENO)
		close(node->in_fd);
	if (node->out_fd != STDOUT_FILENO)
		close(node->out_fd);
	free(node);
}

static void	clean_and_exit(t_data *mish)
{
	if (mish)
	{
		if (mish->env)
			hashmap_free_table(mish->env);
		if (mish->cmds)
			ft_lstclear(&mish->cmds, free_scmd);
		if (mish->pids)
			free(mish->pids);
	}
	exit(mish->exit_status);
}

// Prints error message. If is_exit is set tottrue (1), frees the 
// allocated memory and exits with g_exit_status
void	handle_exit(t_data *mish, char *param, int err, int is_exit)
{
	if (err == FORK_ERR || err == PIPE_ERR || err == HIS_WRONG_ARG
		|| err == HIS_WRONG_ARGS || err == CD_ERR || err == NOT_DIR)
		mish->exit_status = 1;
	else if (err == SYNTAX_ERR)
		mish->exit_status = 2;
	else if (err == CMD_NOT_FOUND)
		mish->exit_status = 127;
	else if (err == IS_DIR)
		mish->exit_status = 126;
	else
		mish->exit_status = err;
	if (err != SUCCESS && err != FAILURE && err != ERROR)
		print_error(param, err);
	if (mish && mish->cmds)
		close_fds(mish, NULL);
	if (is_exit)
		clean_and_exit(mish);
}
