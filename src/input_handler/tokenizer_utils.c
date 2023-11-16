/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:35:28 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/15 13:54:46 by sebasnadu        ###   ########.fr       */
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
	ft_matrixfree(mtx);
	*mtx = tmp;
	return (*mtx);
}

static char	**fill_subwords(char **subwords, char *str, char *set, int i[3])
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

char	**split_subwords(const char *str, char *set)
{
	char	**subwords;
	int		len;
	int		index[3];

	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	if (!str)
		return (NULL);
	len = count_subwords((char *)str, set, 0);
	if (len == -1)
		return (NULL);
	subwords = malloc((len + 1) * sizeof(char *));
	if (!subwords)
		return (NULL);
	subwords = fill_subwords(subwords, (char *)str, set, index);
	subwords[len] = NULL;
	return (subwords);
}

static char	**fill_array(char **words, const char *str, char *set, int i[3])
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

char	**split_in_words(char *str, char *set)
{
	char	**words;
	int		size;
	int		counts[2];
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!str)
		return (NULL);
	size = count_words(str, set, counts);
	if (size == -1)
		return (NULL);
	words = ft_calloc(size + 1, sizeof(char *));
	if (!words)
		return (NULL);
	words = fill_array(words, str, set, i);
	return (words);
}
