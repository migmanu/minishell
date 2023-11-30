/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:14:44 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/29 17:32:41 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

static void	hashmap_replace_item(t_hash_item *current, char *value,
		t_hash_item *new_item, int custom)
{
	free(current->value);
	current->value = NULL;
	current->value = ft_strdup(value);
	current->custom = custom;
	hashmap_free_item(new_item);
}

static int	hashmap_insert_item(t_hashmap *table, t_hash_item *new_item,
						unsigned long int index)
{
	if (table->count == table->size)
	{
		handle_exit(NULL, NULL, HASH_FULL, NOT_EXIT);
		hashmap_free_item(new_item);
		return (0);
	}
	table->items[index] = new_item;
	table->count++;
	return (1);
}

t_hash_item	*hashmap_insert(char *key, char *value, t_hashmap *table,
		int custom)
{
	unsigned long int	index;
	t_hash_item			*new_item;
	t_hash_item			*current;

	if (!key)
		return (NULL);
	index = hash(key, table->size);
	new_item = hashmap_create_item(key, value, custom);
	current = table->items[index];
	if (current == NULL)
	{
		if (!hashmap_insert_item(table, new_item, index))
			return (NULL);
	}
	else
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			hashmap_replace_item(current, value, new_item, custom);
		}
		else
			hashmap_handle_collision(table, index, new_item, custom);
	}
	return (new_item);
}
