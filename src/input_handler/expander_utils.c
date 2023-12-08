/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 19:46:07 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/12/08 14:28:50 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_var(char *str, int i, t_data *mish, char *tmp)
{
	char	*var;

	if (str[i] == '$')
		var = ft_itoa((int)mish->pid);
	else if (str[i] == '?')
		var = ft_itoa(mish->exit_status);
	else if (ft_strncmp(tmp, "UID", 4) == 0)
		var = ft_itoa(mish->uid);
	else
		var = ft_strdup(hashmap_search(mish->env, tmp));
	if (!var && (str[i] == '\'' || str[i] == '\"'))
		var = ft_strdup(tmp);
	else if (!var && find_inset(&str[i], "!@#%^&|\"\'$?<> ") == -1
		&& i > 0 && ft_strchr("=", str[i - 1]))
		var = NULL;
	else if (!var)
		var = ft_strdup("");
	return (var);
}

static char	*get_subvars(char *str, int i, t_data *mish)
{
	char	*tmp;
	int		end;
	char	*path;
	char	*var;

	end = find_inset(&str[i], "=!@#%^&|\"\'$?<> ") + (ft_strchr("$?",
				str[i]) != 0);
	if (!end && (str[i] == '\'' || str[i] == '\"'))
		end += find_inset(&str[i + 1], "\"\'") + 1;
	if (end == -1)
		end = ft_strlen(str) - 1;
	tmp = ft_substr(str, i, end);
	var = get_var(str, i, mish, tmp);
	free(tmp);
	tmp = ft_substr(str, 0, i - 1);
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
					&& find_inset(&str[i + 1], "=/~%^{}:; ")) || (quotes[1]
					&& find_inset(&str[i + 1], "=/~%^{}:;\"\' "))))
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
