/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:20:01 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/12 19:42:01 by sebasnadu        ###   ########.fr       */
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

char	*get_subvars(char *str, int i, t_data *mish)
{
	char	*tmp;
	int		end;
	char	*path;
	char	*var;

	end = find_inset(&str[i], "|\"\'$?<> ") + (ft_strchr("$?", str[i]) != 0);
	if (end == -1)
		end = ft_strlen(str);
	tmp = ft_substr(str, i, end);
	var = ft_strdup(hashmap_search(mish->env, tmp));
	free(tmp);
	tmp = ft_substr(str, 0, i - 1);
	if (!var && str[i] == '$')
		var = ft_itoa(mish->pid);
	else if (!var && str[i] == '?')
		var = ft_itoa(666);
	path = ft_strjoin(tmp, var);
	free(tmp);
	free(var);
	tmp = ft_strjoin(path, &str[i + end]);
	free(path);
	free(str);
	return (tmp);
}

char	*expand_vars(t_data *mish, char *str, int quotes[2], int i)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && str[i] == '$' && str[i + 1] && ((!quotes[1]
					&& find_inset(&str[i + 1], "/~%^{}:; ")) || (quotes[1]
					&& find_inset(&str[i + 1], "/~%^{}:;\""))))
			return (expand_vars(mish, get_subvars(str, ++i, mish), quotes, -1));
	}
	return (str);
}

char	*expand_home(char *str, int i, int quotes[2], char *home)
{
	char	*tmp;
	char	*path;

	quotes[0] = 0;
	quotes[0] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && str[i] == '~' && str[i + 1] != '~'
			&& (i == 0 || str[i - 1] != '$'))
		{
			tmp = ft_substr(str, 0, i);
			path = ft_strjoin(tmp, home);
			free(tmp);
			tmp = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, tmp);
			free(tmp);
			free(path);
			return (expand_home(str, i + ft_strlen(home) - 1, quotes, home));
		}
	}
	free(home);
	return (str);
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
