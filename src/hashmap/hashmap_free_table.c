/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_free_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:02:46 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/08 15:07:07 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hashmap_free_table(t_hashmap *table)
{
	unsigned int	i;
	t_hash_item		*current;
	t_hash_item		*tmp;

	i = 0;
	while (i < table->size)
	{
		current = table->items[i];
		while (current != NULL)
		{
			tmp = current->next;
			hashmap_free_item(current);
			current = tmp;
		}
		i++;
	}
	free(table->items);
	free(table);
}
