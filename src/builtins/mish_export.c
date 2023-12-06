/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:25:59 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/06 12:22:04 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_hashmap_custom(t_hashmap *env, char *key)
{
	unsigned long int	index;
	t_hash_item			*current;

	index = hash(key, env->size);
	current = env->items[index];
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
			return (current->custom);
		current = current->next;
	}
	return (1);
}

// Separates vars into key and value. Does not check for proper format. 
static void	get_key_and_value(char **vars, char **key, char **value, int c[])
{
	if (ft_strchr(vars[c[0]], '=') == NULL)
	{
		*key = ft_strdup(vars[c[0]]);
		*value = ft_strdup("");
	}
	else
	{
		c[1] = ft_chr_pos(vars[c[0]], '=');
		*key = ft_substr(vars[c[0]], 0, c[1]);
		if (c[1] == -1)
			*value = ft_strdup("");
		else
			*value = ft_substr(vars[c[0]], ++c[1], ft_strlen(vars[c[0]]));
	}
}

// This function returns 0 when error
static int	add_custom_vars(t_data *mish, char **vars, int c[])
{
	char	*key;
	char	*value;
	int		custom;

	while (vars[c[0]] != NULL && c[2] == 1)
	{
		get_key_and_value(vars, &key, &value, c);
		if (check_key(key, -1, 1) == 0)
		{
			c[0]++;
			continue ;
		}
		custom = get_hashmap_custom(mish->env, key);
		search_and_delete(mish, key);
		c[2] = (hashmap_insert(key, value, mish->env, custom) != NULL);
		free(key);
		free(value);
		c[0]++;
	}
	return (c[2]);
}

static int	export_loop(t_data *mish, t_scmd cmd, int *c)
{
	int	result;
	int	i;

	result = SUCCESS;
	i = 1;
	while (cmd.full_cmd[i] != NULL)
	{
		if (check_key(cmd.full_cmd[i], -1, 1) == 0)
		{
			ft_putstr_fd("mish: export: ", STDERR_FILENO);
			ft_putstr_fd(cmd.full_cmd[i], STDERR_FILENO);
			ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
			result = FAILURE;
		}
		else 
		{
			if (add_custom_vars(mish, cmd.full_cmd, c) == 0)
				result = HASH_FULL;
		}
		i++;
	}
	return (result);
}

// Imitates the bash function export. Works with no flags.
// If if_exit set to true (1), mish_cd will kill 
// current process. False used for when only one 
// builtin command inputed. If no arg, it just prints
// current custom vars.
void	mish_export(t_data *mish, t_scmd cmd, int if_exit)
{
	int	c[3];
	int	result;

	if (cmd.full_cmd[1] == NULL)
	{
		hashmap_print_table(mish->env, 1);
		handle_exit(mish, NULL, SUCCESS, if_exit);
		return ;
	}
	c[0] = 1;
	c[1] = 0;
	c[2] = 1;
	result = export_loop(mish, cmd, c);
	handle_exit(mish, NULL, result, if_exit);
}
