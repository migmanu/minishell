/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:08:00 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/03 20:30:52 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	add_envp(t_hashmap *envs, char *str)
{
	char	*key;
	char	*value;
	int		e;

	e = ft_chr_pos(str, '=');
	if (e == 0 && str[e + 1] == '\0')
		e++;
	key = ft_substr(str, 0, e);
	value = ft_substr(str, ++e, ft_strlen(str));
	if (hashmap_search(envs, key) != NULL)
	{
		if (hashmap_delete(envs, key) == FAILURE)
			return (FAILURE);
	}
	if (hashmap_insert(key, value, envs, 0) == NULL)
		return (FAILURE);
	free(key);
	free(value);
	return (SUCCESS);
}

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

// TODO: name actual failed command
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
