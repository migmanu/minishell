/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_search_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:39:00 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/30 11:39:15 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_hash_item	*hashmap_search_key(t_hashmap *table, char *key)
{
	unsigned long int	index;
	t_hash_item			*current;

	index = hash(key, table->size);
	current = table->items[index];
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
