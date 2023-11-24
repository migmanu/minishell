/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_print_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:16:26 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/24 17:53:07 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_env(t_hash_item *env, int only_customs)
{
	ft_putendl_fd("----------------------------", 1);
	ft_putstr_fd("| ", 1);
	if (only_customs == 1)
		ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env->key, 1);
	ft_putstr_fd(" | = | ", 1);
	ft_putstr_fd(env->value, 1);
	ft_putendl_fd(" |", 1);
}

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
			print_env(current, only_customs);
			current = tmp;
		}
		i++;
	}
	ft_putendl_fd("----------------------------", 1);
}
