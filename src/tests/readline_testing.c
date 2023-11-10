/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_testing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:21:59 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/10 15:28:15 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Initiates user promt with readlie function. Str is an enviroment
// variable that is to be display in the promt, like USER.
void	init_prompt(t_data *mish)
{
	char	*symbol;
	char	*var;
	char	*prompt;
	char	*line;

	symbol = "\033[1;36m $_> \033[0;0m";
	var = hashmap_search(mish->env, "USER");
	if (var)
	{
		prompt = ft_strjoin(var, symbol);
	}
	else
		prompt = ft_strdup(symbol);
	while (1)
	{
		config_signals();
		line = readline(prompt);
		if (line)
		{
			add_history(line);
			if (ft_strncmp(line, "exit", 4) == 0)
			{
				free(prompt);
				mish_error(mish, NULL, SUCCESS, 1);
			}
			input_handler(line, mish);
		}
		else
		{
			exit(SUCCESS);
		}
	}
	free(prompt);
}
