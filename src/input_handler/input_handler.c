/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:20:01 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/12/08 16:55:44 by jmigoya-         ###   ########.fr       */
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

static void	redefine_matrix(char **matrix, int i, int matrix_len)
{
	int		j;
	char	*tmp;

	j = 0;
	while (j < matrix_len)
	{
		if (j < i)
			j++;
		else
		{
			tmp = matrix[j];
			matrix[j] = matrix[j + 1];
			matrix[j + 1] = tmp;
			j++;
		}
	}
}

static void	expander(t_data *mish, char **tokens)
{
	int	i;
	int	quotes[2];
	int	matrix_len;

	matrix_len = ft_matrixlen(tokens);
	i = 0;
	while (tokens && tokens[i])
	{
		if (i > 1 && (tokens[i - 1] && tokens[i - 2]) && tokens[i - 1][0] == '<'
				&& tokens[i - 2][0] == '<')
		{
			i++;
			continue ;
		}
		tokens[i] = expand_vars(mish, tokens[i], quotes, -1);
		tokens[i] = expand_home(tokens[i], -1, quotes,
				ft_strdup(hashmap_search(mish->env, "HOME")));
		if (!tokens[i])
			redefine_matrix(tokens, i, matrix_len);
		else
			i++;
	}
}

static t_list	*fill_syntax_list(char **tokens, int i, t_data *mish)
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
		cmds[1]->content = get_node(cmds[1]->content, tmp, &i, mish);
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
	mish->cmds = fill_syntax_list(tokens, -1, mish);
	return (mish);
}
