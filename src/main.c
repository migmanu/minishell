/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:50:52 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/08 16:11:52 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		exit(1);
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

int	main(int argc, char *argv[], char *envp[])
{
	t_hashmap	*env;
	t_hashmap	*local_vars;

	if (argc != 1)
	{
		printf("minishell takes no arguments, you passed %s\n", argv[1]);
		exit(ERROR);
	}
	env = env_to_hash(envp);
	local_vars = hashmap_create_table(50);
	hashmap_print_table(env);
	init_promt("USER");
	return (0);
}
