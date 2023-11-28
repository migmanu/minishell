/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_create_item.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:26:34 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/28 16:30:43 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_hash_item	*hashmap_create_item(char *key, char *value, int custom)
{
	t_hash_item	*new_item;

	new_item = (t_hash_item *)ft_calloc(sizeof(t_hash_item), 1);
	new_item->key = ft_strdup(key);
	new_item->value = ft_strdup(value);
	new_item->custom = custom;
	new_item->next = NULL;
	return (new_item);
}
