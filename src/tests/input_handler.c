/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:46:38 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/10 11:45:11 by sebasnadu        ###   ########.fr       */
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

char	**split_subwords(const char *str, char *set)
{
	char	**tmp;
	int		len;
	int		counters[2];

	if (!str)
		return (NULL);
	counters[0] = 0;
	counters[1] = 0;
	len = count_words(str, set, counters);
	if (len == -1)
		return (NULL);
	return (NULL);
}

void	split_operators(char **tokens)
{
	char	**subwords;
	int		i;

	i = -1;
	while (tokens && tokens[++i])
	{
		subwords = split_subwords(tokens[i], "<|>");
	}
	(void)subwords;
}

//TODO: continue with parse_and_expand function
void	*input_handler(char *line, t_data *mish)
{
	char	**tokens;
	int		i;

	tokens = split_in_words(line, " ");
	split_operators(tokens);
	free(line);
	if (!tokens)
	{
		mish_error(mish, NULL, UNQUOTE, 0);
		return ("");
	}
	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i++]);
	}
	ft_free_matrix(tokens);
	return (mish);
}
