/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:43:48 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/07 17:44:22 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	else if (err == NO_FILE || err == CD_ERR)
		ft_putstr_fd(": No such file or directory", STDERR_FILENO);
	else if (err == NOT_DIR)
		ft_putstr_fd(": Not a directory", STDERR_FILENO);
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
