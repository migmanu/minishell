/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:43:12 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/10 16:46:13 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_promt(t_data mish, char *str)
{
	char	*symbol;
	char	*var;
	char	*prompt;
	char	*line;

	symbol = "\033[1;36m $_> \033[0;0m";
	var = hashmap_search(mish.env, str);
	if (var)
	{
		prompt = ft_strjoin(var, symbol);
	}
	else
	{
		prompt = ft_strdup(symbol);
	}
	return (prompt);
}
