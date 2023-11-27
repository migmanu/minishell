/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mish_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:25:59 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/27 16:20:42 by johnavar         ###   ########.fr       */
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
		if (ft_strchr(vars[i], '=') == NULL)
		{
			hashmap_insert(vars[i], NULL, mish->env, 1);
			i++;
			continue ;
		}
		c = ft_chr_pos(vars[i], '=');
		key = ft_substr(vars[i], 0, c);
		value = ft_substr(vars[i], ++c, ft_strlen(vars[i]));
		hashmap_insert(key, value, mish->env, 1);
		/*free(key);*/
		/*free(value);*/
		i++;
	}
}

void	mish_export(t_data *mish, t_scmd cmd, int if_exit)
{
	if (cmd.full_cmd[1] == NULL)
	{
		hashmap_print_table(mish->env, 1);
		handle_exit(mish, NULL, SUCCESS, if_exit);
		return ;
	}
	if (cmd.full_cmd[1][0] == '\0')
	{
		ft_putstr_fd("mish: export: `': not a valid identifier\n", \
		STDERR_FILENO);
		handle_exit(mish, NULL, FAILURE, if_exit);
		return ;
	}
	add_custom_vars(mish, cmd.full_cmd);
	handle_exit(mish, NULL, SUCCESS, if_exit);
}
