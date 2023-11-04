/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_testing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:21:59 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/04 15:47:44 by migmanu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		line = readline(promt);
		add_history(line);
	}
	free(promt);
}

int	main(void)
{
	init_promt("USER");
	return (0);
}
