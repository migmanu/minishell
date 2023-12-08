/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:08:00 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/08 16:17:34 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Checks for valid format, which is different
// than the required by export. env only
// requires a string with an '=' sign
// Returns 1 if valid.
static int	check_var_format(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static t_hashmap	*copy_envs(t_hashmap *src)
{
	char		**matrix;
	t_hashmap	*dest;

	hashmap_to_matrix(src, &matrix, 0, 0);
	dest = env_to_hash(matrix);
	ft_matrixfree(&matrix);
	return (dest);
}

static void	exit_mish_env(t_data *mish, char *cmd,
	t_hashmap *env_cpy, int is_exit)
{
	hashmap_free_table(env_cpy);
	handle_exit(mish, cmd, NO_FILE, is_exit);
}

// Checks if any of the words passed after the env command
// should be treated as a command and if it should replace
// env.
static void	check_if_cmd(t_data *mish, t_scmd *cmd)
{
	int		i;
	char	*path;

	i = 1;
	while (cmd->full_cmd[i] != NULL)
	{
		if (check_var_format(cmd->full_cmd[i]) == 1)
		{
			i++;
			continue ;
		}
		path = get_path(mish, cmd->full_cmd[i]);
		if (path == NULL)
			return ;
		free(cmd->full_cmd[0]);
		cmd->full_cmd[0] = NULL;
		cmd->full_cmd = cmd->full_cmd + 1;
		exec_cmd(mish, cmd);
		i++;
	}
}

// Imitates the bash function env. Works with no flags.
// Makes a copy of the mish envp and works with that.
// If if_exit set to true (1), mish_cd will kill 
// current process. False used for when only one 
// builtin command inputed.
void	mish_env(t_data *mish, t_scmd cmd, int if_exit)
{
	t_hashmap	*env_cpy;
	int			i;

	env_cpy = copy_envs(mish->env);
	if (!env_cpy)
		return ;
	check_if_cmd(mish, &cmd);
	i = 1;
	while (cmd.full_cmd[i] != NULL)
	{
		if (check_var_format(cmd.full_cmd[i]) == 0
			|| add_envp(env_cpy, cmd.full_cmd[i]) == FAILURE)
		{
			exit_mish_env(mish, cmd.full_cmd[i], env_cpy, if_exit);
			return ;
		}
		i++;
	}
	hashmap_print_table(env_cpy, PRT_ENV);
	hashmap_free_table(env_cpy);
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
