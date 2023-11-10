/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_promt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:43:12 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/10 17:10:08 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_prompt(t_data mish, char *str)
{
	char	*symbol;
	char	*var;
	char	*prompt;
	char	*color;

	symbol = " $_> \033[0;0m";
	var = hashmap_search(mish.env, str);
	if (var)
	{
		color = ft_strjoin("\033[1;36m", var);
		prompt = ft_strjoin(color, symbol);
		free(color);
	}
	else
	{
		prompt = ft_strdup(symbol);
	}
	return (prompt);
}

char	*init_prompt(t_data *mish)
{
	char	*prompt;
	char	*line;

	prompt = create_prompt(*mish, "USER");
	line = readline(prompt);
	free(prompt);
	if (line)
	{
		add_history(line);
	}
	else
	{
		exit(SUCCESS);
	}
	return (line);
}
