/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_print_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:16:26 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/08 15:58:26 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hashmap_print_table(t_hashmap *table)
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
			ft_putendl_fd("----------------------------", 1);
			ft_putstr_fd("| ", 1);
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd(" | = | ", 1);
			ft_putstr_fd(current->value, 1);
			ft_putendl_fd(" |", 1);
			current = tmp;
		}
		i++;
	}
	ft_putendl_fd("----------------------------", 1);
}
