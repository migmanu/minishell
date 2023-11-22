/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:20:01 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/22 15:55:38 by johnavar         ###   ########.fr       */
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
		ft_matrixfree(&subwords);
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

static t_list	*fill_syntax_list(char **tokens, int i)
{
	char	**tmp[2];
	t_list	*cmds[2];

	tmp[0] = trim_all(tokens);
	tmp[1] = tokens;
	cmds[0] = NULL;
	while (tokens[++i])
	{
		cmds[1] = ft_lstlast(cmds[0]);
		if (i == 0 || (tokens[i][0] == '|' && tokens[i + 1]
			&& tokens[i + 1][0]))
		{
			i += tokens[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(init_node()));
			cmds[1] = ft_lstlast(cmds[0]);
		}
		cmds[1]->content = get_node(cmds[1]->content, tmp, &i);
		if (i < 0)
			return (clean_fail(cmds[0], tokens, tmp[0]));
		if (!tokens[i])
			break ;
	}
	ft_matrixfree(&tmp[0]);
	ft_matrixfree(&tokens);
	return (cmds[0]);
}

void	*input_handler(char *line, t_data *mish)
{
	char	**tokens;

	tokens = tokenizer(line);
	free(line);
	if (!tokens)
	{
		handle_exit(mish, NULL, UNQUOTE, NOT_EXIT);
		return ("");
	}
	expander(mish, tokens);
	mish->cmds = fill_syntax_list(tokens, -1);
	return (mish);
}
