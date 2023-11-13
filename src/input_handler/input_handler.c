/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:20:01 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/13 19:48:29 by johnavar         ###   ########.fr       */
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
	tmp[size] = NULL;
	i = -1;
	while (tokens[++i])
		tmp[i] = ft_strdup(tokens[i]);
	return (tmp);
}

int	len_noquotes(char *str)
{
	int	i;
	int	quotes[2];
	int	count;

	quotes[0] = 0;
	quotes[1] = 0;
	count = 0;
	i = -1;
	while (str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if ((!quotes[1] && str[i] == '\'') || (!quotes[0] && str[i] == '\"'))
			count++;
	}
	if (quotes[0] || quotes[1])
		return (-1);
	return (count);
}

char	*get_trimmed_str(char *str)
{
	int		size;
	char	*tmp;
	int		i[2];
	int		quotes[2];

	size = len_noquotes(str);
	tmp = malloc((ft_strlen(str) - size + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i[0] = -1;
	i[1] = -1;
	quotes[0] = 0;
	quotes[1] = 0;
	if (!str || size == -1)
		return (NULL);
	while (str[++i[0]])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i[0]] == '\''));
		quotes[1] = (quotes[1] + (!quotes[0] && str[i[0]] == '\"'));
		if ((quotes[1] || str[i[0]] != '\'') && (quotes[0] || str[i[0]] != '\"')
			&& ++i[1] >= 0)
			tmp[i[1]] = str[i[0]];
	}
	tmp[++i[1]] = NULL;
	return (tmp);
}

char	**trim_quotes(char **tokens)
{
	char	**clean_tokens;
	char	*tmp;
	int		i;

	clean_tokens = ft_matrixdup(tokens);
	i = -1;
	while (clean_tokens[++i])
	{
		tmp = get_trimmed_str(clean_tokens[i]);
		free(clean_tokens[i]);
		clean_tokens[i] = tmp;
	}
	return (clean_tokens);
}

t_list	*ft_lstgetlast(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

t_scmd	*init_node(void)
{
	t_scmd	*node;

	node = malloc(sizeof(t_scmd));
	if (!node)
		return (NULL);
	node->full_cmd = NULL;
	node->path = NULL;
	node->in_fd = STDIN_FILENO;
	node->out_fd = STDOUT_FILENO;
	return (node);
}

t_scmd	*get_data(t_scmd *node, char *cmds, int *i)
{
	if (cmds[*i][0] )
}

t_list	*fill_syntax_list(t_data *mish, char **tokens)
{
	char	**tmp[2];
	t_list	*cmds[2];
	int		i;

	tmp[0] = trim_quotes(tokens);
	tmp[1] = tokens;
	cmds[0] = NULL;
	i = -1;
	while (tokens[++i])
	{
		cmds[1] = ft_lstgetlast(cmds[0]);
		if ((i == 0 || tokens[i][0] == '|')
				&& (tokens[i + 1] && tokens[i + 1][0]))
		{
			i += tokens[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(init_node()));
			cmds[1] = ft_lstgetlast(cmds[0]);
		}
		cmds[1]->content = get_data(cmds[1]->content, tmp[1], &i);
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
	mish->cmds = fill_syntax_list(mish, tokens);
	ft_free_matrix(&tokens);
	return (mish);
}
