/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:36:41 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/11 15:52:41 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**fill_subwords(char **subwords, char *str, char *set, int i[3])
{
	int	quote[2];

	quote[0] = 0;
	quote[1] = 0;
	while (str && str[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(set, str[i[0]]))
		{
			while ((!ft_strchr(set, str[i[0]]) || quote[0] || quote[1])
				&& str[i[0]])
			{
				quote[0] = (quote[0] + (!quote[1] && str[i[0]] == '\'')) % 2;
				quote[1] = (quote[1] + (!quote[0] && str[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		subwords[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (subwords);
}

int	ft_matrixlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	return (i);
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

char	**fill_array(char **words, const char *str, char *set, int i[3])
{
	int	len;
	int	quote[2];

	quote[0] = 0;
	quote[1] = 0;
	len = ft_strlen(str);
	while (str[i[0]])
	{
		while (ft_strchr(set, str[i[0]]) && str[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, str[i[0]]) || quote[0] || quote[1])
			&& str[i[0]])
		{
			quote[0] = (quote[0] + (!quote[1] && str[i[0]] == '\'')) % 2;
			quote[1] = (quote[1] + (!quote[0] && str[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= len)
			words[i[2]++] = NULL;
		else
			words[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
	}
	return (words);
}
