/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:55:28 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/12/04 12:36:01 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_mish_history(t_data *mish, char *line)
{
	char	*tmp;

	tmp = ft_strdup(line);
	if (!tmp)
		return ;
	mish->history = ft_extend_matrix(mish->history, tmp);
	free(tmp);
}

static char	*dup_key(char *env_line)
{
	char	*key;
	int		i;

	i = 0;
	while (env_line[i] != '=')
		i++;
	key = ft_substr(env_line, 0, i);
	return (key);
}

static char	*dup_value(char *env_line)
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

t_hashmap	*env_to_hash(char **env)
{
	t_hashmap	*table;
	int			len;
	char		*key;
	char		*value;
	int			i;

	len = 0;
	i = -1;
	while (env[len])
		len++;
	if (len)
		table = hashmap_create_table(len * 2);
	else
		table = hashmap_create_table(100);
	if (!table)
		exit(FAILURE);
	while (++i < len)
	{
		key = dup_key(env[i]);
		value = dup_value(env[i]);
		hashmap_insert(key, value, table, 0);
		free(key);
		free(value);
	}
	return (table);
}
