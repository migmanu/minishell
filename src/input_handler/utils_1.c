/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:50:41 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/11 15:52:25 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**insert_subwords(char ***mtx, char **new_items, int pos)
{
	char	**tmp;
	int		i[3];

	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
	if (!mtx || !*mtx || pos < 0 || pos >= ft_matrixlen(*mtx))
		return (NULL);
	tmp = ft_calloc(ft_matrixlen(*mtx) + ft_matrixlen(new_items),
			sizeof(char *));
	while (tmp && mtx[0][++i[0]])
	{
		if (i[0] != pos)
			tmp[++i[1]] = ft_strdup(mtx[0][i[0]]);
		else
		{
			while (new_items && new_items[++i[2]])
				tmp[++i[1]] = ft_strdup(new_items[i[2]]);
		}
	}
	ft_free_matrix(mtx);
	*mtx = tmp;
	return (*mtx);
}
