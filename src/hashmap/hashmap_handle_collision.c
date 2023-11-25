/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_handle_collision.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:08:15 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/24 16:47:53 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hashmap_handle_collision(t_hashmap *table, unsigned long int index,
									t_hash_item *new_item, int custom)
{
	t_hash_item	*current;

	current = table->items[index];
	while (current->next != NULL)
		current = current->next;
	current->next = new_item;
	current->next->custom = custom;
	current->next->next = NULL;
	table->count++;
}
