/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_testing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:21:59 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/04 14:40:28 by migmanu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(void)
{
	char	*promt;
	char	*line;

	promt = "_> ";
	while (1)
	{
		line = readline(promt);
		add_history(line);
	}
}
