/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:12:58 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/11/21 22:13:23 by jmigoya-         ###   ########.fr       */
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
