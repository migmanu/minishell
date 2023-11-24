/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_print_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:16:26 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/24 16:30:21 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	hashmap_print_table(t_hashmap *table, int only_customs)
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
			if (only_customs == 1 && current->custom != 1)
			{
				current = current->next;
				continue ;
			}
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
