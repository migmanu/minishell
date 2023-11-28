/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:25:59 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/28 19:16:42 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_hashmap_custom(t_hashmap *env, char *key)
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

static void	add_custom_vars(t_data *mish, char **vars, int i)
{
	char	*key;
	char	*value;
	int		c;

	while (vars[++i] != NULL)
	{
		if (ft_strchr(vars[i], '='))
		{
			c = ft_chr_pos(vars[i], '=');
			key = ft_substr(vars[i], 0, c);
			if (c == -1)
				value = ft_strdup("");
			else
				value = ft_substr(vars[i], ++c, ft_strlen(vars[i]));
		}
		else
		{
			key = ft_strdup(vars[i]);
			value = ft_strdup("");
		}
		hashmap_insert(key, value, mish->env,
			get_hashmap_custom(mish->env, key));
		free(key);
		free(value);
	}
}

void	mish_export(t_data *mish, t_scmd cmd, int if_exit)
{
	if (cmd.full_cmd[1] == NULL)
	{
		hashmap_print_table(mish->env, 1);
		handle_exit(mish, NULL, SUCCESS, if_exit);
		return ;
	}
	add_custom_vars(mish, cmd.full_cmd, 0);
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
