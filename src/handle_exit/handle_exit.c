/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johnavar <johnavar@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:45:19 by johnavar          #+#    #+#             */
/*   Updated: 2023/12/04 13:21:54 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	exit(g_exit_status);
}

void	print_error2(int err)
{
	if (err == CMD_NOT_FOUND)
		ft_putstr_fd(": command not found", STDERR_FILENO);
	else if (err == IS_DIR)
		ft_putstr_fd(": is a directory", STDERR_FILENO);
	else if (err == HIS_WRONG_ARG)
		ft_putstr_fd(": numeric argument required", STDERR_FILENO);
	else if (err == HIS_WRONG_ARGS)
		ft_putstr_fd("too many arguments", STDERR_FILENO);
}

void	print_error(char *param, int err)
{
	ft_putstr_fd("mish: ", STDERR_FILENO);
	if (err == INV_ARGS)
		ft_putstr_fd("No arguments needed: ", STDERR_FILENO);
	else if (err == FORK_ERR)
		ft_putstr_fd("Fork error.", STDERR_FILENO);
	else if (err == UNQUOTE)
		ft_putstr_fd("Unmatch quote", STDERR_FILENO);
	else if (err == NO_FILE)
		ft_putstr_fd("No such file or directory: ", STDERR_FILENO);
	else if (err == NO_PERM)
		ft_putstr_fd("Permission denied: ", STDERR_FILENO);
	else if (err == PIPE_ERR)
		ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	else if (err == SYNTAX_ERR)
		ft_putstr_fd("syntax error near unexpected token ", STDERR_FILENO);
	else if (err == HASH_FULL)
		ft_putstr_fd("Insert Error: Hash Table is full", STDERR_FILENO);
	else if (err == NO_MEM)
		ft_putstr_fd("No memory left on device: ", STDERR_FILENO);
	else if (err == HIS_WRONG_ARG || err == HIS_WRONG_ARGS)
		ft_putstr_fd("history: ", STDERR_FILENO);
	if (param)
		ft_putstr_fd(param, STDERR_FILENO);
	print_error2(err);
	ft_putstr_fd("\n", STDERR_FILENO);
}

// Prints error message. If is_exit is set tottrue (1), frees the 
// allocated memory and exits with g_exit_status
void	handle_exit(t_data *mish, char *param, int err, int is_exit)
{
	if (err == FORK_ERR || err == PIPE_ERR || err == HIS_WRONG_ARG
		|| err == HIS_WRONG_ARGS)
		g_exit_status = 1;
	else if (err == SYNTAX_ERR)
		g_exit_status = 2;
	else if (err == CMD_NOT_FOUND)
		g_exit_status = 127;
	else if (err == IS_DIR)
		g_exit_status = 126;
	else
		g_exit_status = err;
	if (err != SUCCESS && err != FAILURE && err != ERROR)
		print_error(param, err);
	if (is_exit)
		clean_and_exit(mish);
}
