/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:25:59 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/21 16:47:56 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Returns the index of the first occurance of c 
// in string str. Returns -1 if no c or error
int	ft_chr_pos(const char *str, const char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

// TODO: check, is there a way to just get the exported vars from the
// hash map? Needed for export with no arguments
void	mish_export(t_data *mish, t_scmd cmd, int if_exit)
{
	printf("export init\n");
	char	*key;
	char	*value;
	int		i;

	if (cmd.full_cmd[1] == NULL)
	{
		hashmap_print_table(mish->env); // TODO: show only exported!
		handle_exit(mish, NULL, SUCCESS, if_exit);
		return ;
	}
	if (ft_strchr(cmd.full_cmd[1], '=') == NULL)
		handle_exit(mish, NULL, SUCCESS, if_exit);
	i = ft_chr_pos(cmd.full_cmd[1], '=');
	key = ft_substr(cmd.full_cmd[1], 0, i);
	value = ft_substr(cmd.full_cmd[1], ++i, ft_strlen(cmd.full_cmd[1]));
	if (hashmap_search(mish->env, key) != NULL)
		hashmap_delete(mish->env, key);
	hashmap_insert(key, value, mish->env); // TODO: mark as custom var
	free(key);
	free(value);
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
