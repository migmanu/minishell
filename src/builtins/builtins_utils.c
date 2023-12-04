/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:12:58 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/04 17:59:14 by jmigoya-         ###   ########.fr       */
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

int	add_envp(t_hashmap *envs, char *str)
{
	char	*key;
	char	*value;
	int		e;

	e = ft_chr_pos(str, '=');
	if (e == 0 && str[e + 1] == '\0')
		e++;
	key = ft_substr(str, 0, e);
	value = ft_substr(str, ++e, ft_strlen(str));
	if (hashmap_search(envs, key) != NULL)
	{
		if (hashmap_delete(envs, key) == FAILURE)
			return (FAILURE);
	}
	if (hashmap_insert(key, value, envs, 0) == NULL)
		return (FAILURE);
	free(key);
	free(value);
	return (SUCCESS);
}
