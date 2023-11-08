/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_create_table.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:27:35 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/08 16:09:27 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_hashmap	*hashmap_create_table(unsigned int size)
{
	t_hashmap		*new_table;
	unsigned int	i;

	i = 0;
	new_table = (t_hashmap *)ft_calloc(sizeof(t_hashmap), 1);
	if (!new_table)
		return (NULL);
	new_table->size = size;
	new_table->count = 0;
	new_table->items = (t_hash_item **)ft_calloc(sizeof(t_hash_item *), size);
	if (!new_table->items)
	{
		free(new_table);
		return (NULL);
	}
	while (i < size)
	{
		new_table->items[i] = NULL;
		i++;
	}
	return (new_table);
}
