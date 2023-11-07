/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_testing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:21:59 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/06 18:59:13 by migmanu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Initiates user promt with readlie function. Str is an enviroment
// variable that is to be display in the promt, like USER.
void	init_promt(char *str)
{
	char	*symbol;
	char	*var;
	char	*promt;
	char	*line;

	symbol = " $_> ";
	var = getenv(str);
	if (var)
	{
		promt = ft_strjoin(var, symbol);
	}
	else
		promt = symbol;
	while (1)
	{
		config_signals();
		line = readline(promt);
		add_history(line);
		if (ft_strncmp(line, "exit", 4) == 0)
			exit(SUCCESS);
	}
	free(promt);
}
