/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:46:38 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/10 19:49:06 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_words(const char *str, char *set, int cts[2])
{
	int	quote[2];

	quote[0] = 0;
	quote[1] = 0;
	while (str && str[cts[0]] != '\0')
	{
		cts[1]++;
		if (!ft_strchr(set, str[cts[0]]))
		{
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
			words[i[2]++] = "\0";
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

char	**fill_subwords(char **subwords, char *str, char *set, int i[3])
{
	int	quote[2];

	quote[0] = 0;
	quote[1] = 0;
	while (str && str[i[0]] != '\0')
	{
		if (!ft_strchr(set, str[i[0]]))
		{
			i[1] = i[0];
			while ((!ft_strchr(set, str[i[0]]) || quote[0] || quote[1])
				&& str[i[0]])
			{
				quote[0] = (quote[0] + (!quote[1] && str[i[0]] == '\'')) % 2;
				quote[1] = (quote[1] + (!quote[0] && str[i[0]] == '\"')) % 2;
				++i[0];
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
	int		counters[2];
	int		index[3];

	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	if (!str)
		return (NULL);
	counters[0] = 0;
	counters[1] = 0;
	len = count_words(str, set, counters);
	if (len == -1)
		return (NULL);
	subwords = ft_calloc(len + 1, sizeof(char *));
	subwords = fill_subwords(subwords, (char *)str, set, index);
	return (subwords);
}

int	ft_matrixlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

char	**insert_subwords(char ***mtx, char **new_items, int pos)
{
	char	**tmp;
	int		i[3];

	if (!mtx || !*mtx || pos < 0 || ft_matrixlen(*mtx) <= pos)
		return (NULL);
	tmp = ft_calloc(ft_matrixlen(*mtx) + ft_matrixlen(*mtx), sizeof(char *));
	i[0] = -1;
	i[1] = -1;
	i[2] = -1;
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

char	**split_operators(char **tokens)
{
	char	**subwords;
	int		i;

	i = -1;
	while (tokens && tokens[++i])
	{
		subwords = split_subwords(tokens[i], "<|>");
		tokens = insert_subwords(&tokens, subwords, i);
		i += ft_matrixlen(subwords) - 1;
		ft_free_matrix(&subwords);
	}
	return (tokens);
}

//TODO: continue with parse_and_expand function
void	*input_handler(char *line, t_data *mish)
{
	char	**tokens;
	int		i;

	tokens = split_in_words(line, " ");
	free(line);
	if (!tokens)
	{
		mish_error(mish, NULL, UNQUOTE, 0);
		return ("");
	}
	tokens = split_operators(tokens);
	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i++]);
	}
	ft_free_matrix(&tokens);
	return (mish);
}
