/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:32:07 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/12/04 15:29:31 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	find_free_and_relink(t_hashmap *table, t_hash_item *current,
									char *key)
{
	t_hash_item	*tmp;

	while (current->next != NULL)
	{
		if (ft_strncmp(current->next->key, key, ft_strlen(key) + 1) == 0)
		{
			tmp = current->next;
			current->next = current->next->next;
			hashmap_free_item(tmp);
			table->count--;
			return ;
		}
		current = current->next;
	}
}

static void	free_and_relink(t_hashmap *table, t_hash_item *current,
							unsigned long int index)
{
	table->items[index] = current->next;
	hashmap_free_item(current);
	table->count--;
}

static void	free_and_set_null(t_hashmap *table, t_hash_item *current,
							unsigned long int index)
{
	hashmap_free_item(current);
	table->items[index] = NULL;
	table->count--;
}

// Returns SUCCES (0) if correctly deleted
int	hashmap_delete(t_hashmap *table, char *key)
{
	unsigned long int	index;
	t_hash_item			*current;

	if (!key)
		return (FAILURE);
	index = hash(key, table->size);
	current = table->items[index];
	if (current == NULL)
		free_and_set_null(table, current, index);
	else if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		free_and_relink(table, current, index);
	else
		find_free_and_relink(table, current, key);
	if (hashmap_search(table, key))
		return (FAILURE);
	return (SUCCESS);
}
