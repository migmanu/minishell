/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_testing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:21:59 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/08 21:46:35 by sebasnadu        ###   ########.fr       */
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

	symbol = " $_> ";
	var = hashmap_search(mish->env, "USER");
	if (var)
	{
		prompt = ft_strjoin(var, symbol);
	}
	else
		prompt = symbol;
	while (1)
	{
		config_signals();
		line = readline(prompt);
		add_history(line);
		if (ft_strncmp(line, "exit", 4) == 0)
			exit(SUCCESS);
		input_handler(line, mish);
	}
	free(prompt);
}
