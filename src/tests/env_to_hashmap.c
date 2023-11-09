/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_hashmap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:55:28 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/09 17:56:50 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*dup_key(char *env_line)
{
	char	*key;
	int		i;

	i = 0;
	while (env_line[i] != '=')
		i++;
	key = ft_substr(env_line, 0, i);
	return (key);
}

char	*dup_value(char *env_line)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	while (env_line[i] != '=' && env_line[i] != '\0')
		i++;
	j = i;
	while (env_line[j] != '\0')
		j++;
	value = ft_substr(env_line, i + 1, j);
	return (value);
}

// TODO: Add error handling
// TODO: Handling not envp
t_hashmap	*env_to_hash(char **env)
{
	t_hashmap	*table;
	int			len;
	char		*key;
	char		*value;
	int			i;

	len = 0;
	i = 0;
	while (env[len])
		len++;
	table = hashmap_create_table(len * 2);
	if (!table)
		exit(FAILURE);
	while (i < len)
	{
		key = dup_key(env[i]);
		value = dup_value(env[i]);
		hashmap_insert(key, value, table);
		free(key);
		free(value);
		i++;
	}
	return (table);
}
