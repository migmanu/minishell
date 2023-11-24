/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:14:44 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/24 12:56:52 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hashmap_replace_item(t_hash_item *current, char *value,
					t_hash_item *new_item)
{
	free(current->value);
	current->value = ft_strdup(value);
	hashmap_free_item(new_item);
}

int	hashmap_insert_item(t_hashmap *table, t_hash_item *new_item,
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

t_hash_item	*hashmap_insert(char *key, char *value, t_hashmap *table)
{
	unsigned long int	index;
	t_hash_item			*new_item;
	t_hash_item			*current;

	if (!key)
		return (NULL);
	index = hash(key, table->size);
	new_item = hashmap_create_item(key, value);
	current = table->items[index];
	if (current == NULL)
	{
		if (!hashmap_insert_item(table, new_item, index))
			return (NULL);
	}
	else
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
			hashmap_replace_item(current, value, new_item);
		else
			hashmap_handle_collision(table, index, new_item);
	}
	return (new_item);
}
