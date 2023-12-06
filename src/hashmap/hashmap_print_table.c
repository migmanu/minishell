/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_print_table.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:16:26 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/12/06 16:35:36 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_env(t_hash_item *env, int options)
{
	ft_putendl_fd("----------------------------", 1);
	ft_putstr_fd("| ", 1);
	if (options == PRT_EXP)
		ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env->key, 1);
	ft_putstr_fd(" | = | ", 1);
	if (env->value)
		ft_putstr_fd(env->value, 1);
	ft_putendl_fd(" |", 1);
}

void	hashmap_print_table(t_hashmap *table, int options)
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
			print_env(current, options);
			current = tmp;
		}
		i++;
	}
	ft_putendl_fd("----------------------------", 1);
}
