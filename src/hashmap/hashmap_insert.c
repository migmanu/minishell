/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:14:44 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/08 15:52:55 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// TODO: Add error handling
void	hashmap_insert(char *key, char *value, t_hashmap *table)
{
	unsigned long int	index;
	t_hash_item			*new_item;
	t_hash_item			*current;

	index = hash(key, table->size);
	new_item = hashmap_create_item(key, value);
	current = table->items[index];
	if (current == NULL)
	{
		if (table->count == table->size)
			exit(1);
		table->items[index] = new_item;
		table->count++;
	}
	else
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			hashmap_free_item(new_item);
		}
		else
			hashmap_handle_collision(table, index, new_item);
	}
}
