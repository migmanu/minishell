/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:32:07 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/23 20:54:44 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*clean_fail(t_list *cmds, char **tokens, char **tmp)
{
	ft_lstclear(&cmds, free_scmd);
	ft_matrixfree(&tmp);
	ft_matrixfree(&tokens);
	return (NULL);
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
	tmp[++i[1]] = '\0';
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
