/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:08:00 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/27 11:01:55 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	add_envp(t_hashmap *envs, char *str)
{
	char	*key;
	char	*value;
	int		e;

	e = ft_chr_pos(str, '=');
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

static int	check_var_format(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			return (1);
		if (str[i] == '=')
			break ;
		i++;
	}
	if (ft_strlen(str) == i)
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
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

static void	exit_mish_env(t_data *mish, t_hashmap *env_cpy, int is_exit)
{
	hashmap_free_table(env_cpy);
	handle_exit(mish, NULL, NO_FILE, is_exit);
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
	i = 1;
	while (cmd.full_cmd[i] != NULL)
	{
		if (check_var_format(cmd.full_cmd[i]) == 0 && \
			add_envp(env_cpy, cmd.full_cmd[i]) == FAILURE)
		{
			exit_mish_env(mish, env_cpy, if_exit);
			return ;
		}
		if (check_var_format(cmd.full_cmd[i]) != 0)
		{
			exit_mish_env(mish, env_cpy, if_exit);
			return ;
		}
		i++;
	}
	hashmap_print_table(env_cpy, PRT_ENV);
	hashmap_free_table(env_cpy);
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
