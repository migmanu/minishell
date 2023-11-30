/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:25:59 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/30 11:44:48 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

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

// WARNING: this function returns 0 when error
static int	add_custom_vars(t_data *mish, char **vars, int c[])
{
	char	*key;
	char	*value;
	int		custom;

	while (vars[c[0]] != NULL && c[2] == 1)
	{
		get_key_and_value(vars, &key, &value, c);
		custom = get_hashmap_custom(mish->env, key);
		search_and_delete(mish, key);
		c[2] = (hashmap_insert(key, value, mish->env, custom) != NULL);
		free(key);
		free(value);
		c[0]++;
	}
	return (c[2]);
}

void	mish_export(t_data *mish, t_scmd cmd, int if_exit)
{
	int	c[3];

	c[0] = 1;
	c[1] = 0;
	c[2] = 1;
	if (cmd.full_cmd[1] == NULL)
	{
		hashmap_print_table(mish->env, 1);
		handle_exit(mish, NULL, SUCCESS, if_exit);
		return ;
	}
	if (cmd.full_cmd[1][0] == '\0')
	{
		ft_putstr_fd("mish: export: `': not a valid identifier\n", \
		STDERR_FILENO);
		handle_exit(mish, NULL, FAILURE, if_exit);
		return ;
	}
	if (add_custom_vars(mish, cmd.full_cmd, c) == 0)
	{
		handle_exit(mish, NULL, HASH_FULL, if_exit);
		return ;
	}
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
