/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:35:28 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/11 16:06:48 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
