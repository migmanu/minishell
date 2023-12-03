/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:36:41 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/12/03 14:07:10 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_matrixdup(char **tokens)
{
	int		i;
	int		size;
	char	**tmp;

	if (!tokens || !tokens[0])
		return (NULL);
	size = ft_matrixlen(tokens);
	tmp = malloc((size + 1) * sizeof(char *));
	if (!tmp)
		return (NULL);
	i = -1;
	while (tokens[++i])
	{
		tmp[i] = ft_strdup(tokens[i]);
		if (!tmp[i])
		{
			ft_matrixfree(&tmp);
			return (NULL);
		}
	}
	tmp[i] = NULL;
	return (tmp);
}

int	find_inset(const char *str, char *set)
{
	int	i;

	i = -1;
	if (!str)
		return (i);
	while (str[++i])
		if (ft_strchr(set, str[i]))
			return (i);
	return (-1);
}

int	count_words(const char *str, char *set, int cts[2])
{
	int	quote[2];

	quote[0] = 0;
	quote[1] = 0;
	while (str && str[cts[0]] != '\0')
	{
		if (!ft_strchr(set, str[cts[0]]))
		{
			cts[1]++;
			while ((!ft_strchr(set, str[cts[0]]) || quote[0]) && str[cts[0]])
			{
				if (!quote[1] && (str[cts[0]] == '\"' || str[cts[0]] == '\''))
					quote[1] = str[cts[0]];
				quote[0] = (quote[0] + (str[cts[0]] == quote[1])) % 2;
				quote[1] *= quote[0] != 0;
				cts[0]++;
			}
			if (quote[0])
				return (-1);
		}
		else
			cts[0]++;
	}
	return (cts[1]);
}

int	count_subwords(char *s, char *set, int count)
{
	int		q[2];
	int		i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (s && s[i] != '\0')
	{
		count++;
		if (!ft_strchr(set, s[i]))
		{
			while ((!ft_strchr(set, s[i]) || q[0] || q[1]) && s[i] != '\0')
			{
				q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
				i++;
			}
			if (q[0] || q[1])
				return (-1);
		}
		else
			i++;
	}
	return (count);
}
