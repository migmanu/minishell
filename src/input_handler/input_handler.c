/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:20:01 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/14 21:08:28 by sebasnadu        ###   ########.fr       */
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
	i = -1;
	while (tokens[++i])
	{
		tmp[i] = ft_strdup(tokens[i]);
		if (!tmp[i])
		{
			ft_free_matrix(&tmp);
			return (NULL);
		}
	}
	tmp[i] = NULL;
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
	int		count;
	char	*tmp;
	int		i[2];
	int		quotes[2];

	i[0] = -1;
	i[1] = -1;
	quotes[0] = 0;
	quotes[1] = 0;
	count = len_noquotes(str);
	if (!str || count == -1)
		return (NULL);
	tmp = malloc((ft_strlen(str) - count + 1) * sizeof(char));
	if (!tmp)
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

char	**trim_all(char **tokens)
{
	char	**clean_tokens;
	char	*tmp;
	int		i;

	clean_tokens = ft_matrixdup(tokens);
	i = -1;
	while (clean_tokens && clean_tokens[++i])
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

int	get_fd(int oldfd, char *path, int flags[2])
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (access(path, F_OK) == -1 && !flags[0])
		mish_error(NULL, path, NO_FILE, 0);
	else if (!flags[0] && access(path, R_OK) == -1)
		mish_error(NULL, path, NO_PERM, 0);
	else if (flags[0] && access(path, W_OK) == -1 && access(path, F_OK) == 0)
		mish_error(NULL, path, NO_PERM, 0);
	if (flags[0] && flags[1])
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else if (flags[0] && !flags[1])
		fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (!flags[0] && oldfd != -1)
		fd = open(path, O_RDONLY);
	else
		fd = oldfd;
	return (fd);
}

t_scmd	*redir_out_append(t_scmd *node, char **cmds, int *i)
{
	char	*err;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 1;
	err = "mish: syntax error near unexpected token `newline'";
	(*i)++;
	if (cmds[++(*i)])
		node->out_fd = get_fd(node->out_fd, cmds[*i], flags);
	if (!cmds[*i] || node->out_fd == -1)
	{
		*i = -1;
		if (node->out_fd != -1)
		{
			ft_putstr_fd(err, STDERR_FILENO);
			g_exit_status = 2;
		}
	}
	return (node);
}

t_scmd	*redir_out(t_scmd *node, char **cmds, int *i)
{
	char	*err;
	int		flags[2];

	flags[0] = 1;
	flags[1] = 0;
	err = "mish: syntax error near unexpected token `newline'";
	(*i)++;
	if (cmds[*i])
		node->out_fd = get_fd(node->out_fd, cmds[*i], flags);
	if (!cmds[*i] || node->out_fd == -1)
	{
		*i = -1;
		if (node->out_fd != -1)
		{
			ft_putstr_fd(err, STDERR_FILENO);
			g_exit_status = 2;
		}
		else
			g_exit_status = 1;
	}
}

// TODO:add ctr-c behaviour
char	*get_heredoc_str(char *str[2], size_t len, char *limit, char *err)
{
	char	*tmp;

	while (!str[0] || ft_strncmp(str[0], limit, len)
		|| ft_strlen(str[0]) != len)
	{
		tmp = str[1];
		str[1] = ft_strjoin(str[1], str[0]);
		free(tmp);
		free(str[0]);
		str[0] = readline("> ");
		if (!str[0])
		{
			printf("%s (wanted `%s\')\n", err, limit);
			break ;
		}
		tmp = str[0];
		str[0] = ft_strjoin(str[0], "\n");
		free(tmp);
		len = ft_strlen(str[0]) - 1;
	}
	free(str[0]);
	return (str[1]);
}

int	get_heredoc_fd(void)
{
	int		fd[2];
	char	*err;
	char	*str[2];
	char	*limit;

	str[0] = NULL;
	str[1] = NULL;
	limit = NULL;
	g_exit_status = 0;
	err = "minishell: warning: here-document delimited by end-of-file";
	if (pipe(fd) == -1)
	{
		mish_error(NULL, NULL, PIPE_ERR, 0);
		return (-1);
	}
	str[0] = get_heredoc_str(str, 0, limit, err);
}

t_scmd	*redir_in_heredoc(t_scmd *node, char **cmds, int *i)
{
	char	*err;
	char	*limit;

	limit = NULL;
	err = "mish: syntax error near unexpected token `newline'";
	(*i)++;
	if (cmds[++(*i)])
	{
		tmp = cmds[*i];
		node->in_fd = get_heredoc_fd();
	}
	if (!cmds[*i] || node->in_fd == -1)
	{
		*i = -1;
		if (node->in_fd != -1)
		{
			ft_putstr_fd(err, STDERR_FILENO);
			g_exit_status = 2;
		}
	}
	return (node);
}

t_scmd	*get_data(t_scmd *node, char **cmds[2], int *i)
{
	if (cmds[1][*i])
	{
		if (cmds[1][*i][0] == '>' && cmds[1][*i + 1]
			&& cmds[1][*i + 1][0] == '>')
			node = redir_out_append(node, cmds[0], i);
		else if (cmds[1][*i][0] == '>')
			node = redir_out(node, cmds[0], i);
		else if (cmds[1][*i][0] == '<' && cmds[1][*i + 1]
			&& cmds[1][*i + 1][0] == '<')
			node = redir_in_heredoc(node, cmds[0], i);
	}
}

t_list	*fill_syntax_list(t_data *mish, char **tokens, int i)
{
	char	**tmp[2];
	t_list	*cmds[2];

	tmp[0] = trim_all(tokens);
	tmp[1] = tokens;
	cmds[0] = NULL;
	while (tokens[++i])
	{
		cmds[1] = ft_lstgetlast(cmds[0]);
		if (i == 0 || (tokens[i][0] == '|' && tokens[i + 1]
			&& tokens[i + 1][0]))
		{
			i += tokens[i][0] == '|';
			ft_lstadd_back(&cmds[0], ft_lstnew(init_node()));
			cmds[1] = ft_lstgetlast(cmds[0]);
		}
		cmds[1]->content = get_data(cmds[1]->content, tpm, &i);
		if (i < 0)
			return (NULL);
		if (!args[i])
			break ;
	}
	ft_free_matrix(&tmp[0]);
	ft_free_matrix(&tokens);
	return (cmds[0]);
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
	mish->cmds = fill_syntax_list(mish, tokens, -1);
	ft_free_matrix(&tokens);
	return (mish);
}
