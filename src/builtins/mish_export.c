/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:25:59 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/24 14:29:19 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	add_custom_vars(t_data *mish, char **vars)
{
	char	*key;
	char	*value;
	int		i;
	int		c;

	i = 1;
	while (vars[i] != NULL)
	{
		c = ft_chr_pos(vars[i], '=');
		key = ft_substr(vars[i], 0, c);
		value = ft_substr(vars[i], ++c, ft_strlen(vars[i]));
		if (hashmap_search(mish->env, key) != NULL)
			hashmap_delete(mish->env, key);
		hashmap_insert(key, value, mish->env, 1);
		free(key);
		free(value);
		i++;
	}
}

// TODO: check, is there a way to just get the exported vars from the
// hash map? Needed for export with no arguments
// TODO: check if more than one var per command
void	mish_export(t_data *mish, t_scmd cmd, int if_exit)
{
	if (cmd.full_cmd[1] == NULL)
	{
		hashmap_print_table(mish->env, 1);
		handle_exit(mish, NULL, SUCCESS, if_exit);
		return ;
	}
	if (ft_strchr(cmd.full_cmd[1], '=') == NULL)
	{
		handle_exit(mish, NULL, SUCCESS, if_exit);
		return ;
	}
	add_custom_vars(mish, cmd.full_cmd);
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
