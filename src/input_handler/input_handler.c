/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:20:01 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/12 19:46:45 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**tokenizer(char *line)
{
	char	**words;
	char	**subwords;
	int		i;

	i = -1;
	words = split_in_words(line, " ");
	while (words && words[++i])
	{
		subwords = split_subwords(words[i], "<|>");
		insert_subwords(&words, subwords, i);
		i += ft_matrixlen(subwords) - 1;
		ft_free_matrix(&subwords);
	}
	return (words);
}

static void	expander(t_data *mish, char **tokens)
{
	int	i;
	int	quotes[2];

	i = -1;
	while (tokens && tokens[++i])
	{
		tokens[i] = expand_vars(mish, tokens[i], quotes, -1);
		tokens[i] = expand_home(tokens[i], -1, quotes,
				ft_strdup(hashmap_search(mish->env, "HOME")));
	}
}

//TODO: continue with parse_and_expand function
void	*input_handler(char *line, t_data *mish)
{
	char	**tokens;
	int		i;

	tokens = tokenizer(line);
	free(line);
	if (!tokens)
	{
		mish_error(mish, NULL, UNQUOTE, 0);
		return ("");
	}
	expander(mish, tokens);
	i = 0;
	while (tokens[i])
	{
		printf("%s\n", tokens[i++]);
	}
	ft_free_matrix(&tokens);
	return (mish);
}
