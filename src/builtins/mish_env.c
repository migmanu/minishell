/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:08:00 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/21 22:36:53 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_envp(t_data *mish, char *str)
{
	char	*key;
	char	*value;
	int		e;

	e = ft_chr_pos(str, '=');
	key = ft_substr(str, 0, e);
	value = ft_substr(str, ++e, ft_strlen(str));
	if (hashmap_search(mish->env, key) != NULL)
		hashmap_delete(mish->env, key);
	hashmap_insert(key, value, mish->env); // TODO: mark as custom var
	free(key);
	free(value);
}

// TODO: make copy of envp for this function
void	mish_env(t_data *mish, t_scmd cmd, int if_exit)
{
	int		i;

	printf("mish_env init\n");
	if (cmd.full_cmd[1] == NULL)
	{
		hashmap_print_table(mish->env);
		handle_exit(mish, NULL, SUCCESS, if_exit);
		return ;
	}
	i = 1;
	while (cmd.full_cmd[i] != NULL)
	{
		if (ft_strchr(cmd.full_cmd[i], '=') == NULL)
		{
			handle_exit(mish, cmd.full_cmd[i], NO_FILE, if_exit);
			return ;
		}
		else
		{
			add_envp(mish, cmd.full_cmd[i]);
		}
		i++;
	}
	hashmap_print_table(mish->env);
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
