/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:43:12 by jmigoya-          #+#    #+#             */
/*   Updated: 2023/12/08 14:27:27 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_user_and_uid(t_data *mish)
{
	char	**user;
	char	*tmp;
	char	**env;

	user = NULL;
	tmp = NULL; 
	env = hashmap_to_matrix(mish->env, &env, 0, 0);
	exec(&user, "/usr/bin/id", "id -u", env);
	if (!user)
		user = ft_extend_matrix(user, "-1");
	mish->uid = ft_atoi(user[0]);
	ft_matrixfree(&user);
	user = NULL;
	exec(&user, "/usr/bin/whoami", "whoami", env);
	ft_matrixfree(&env);
	if (!user)
		user = ft_extend_matrix(user, "guest");
	if (!ft_strncmp(user[0], "root", 4))
		tmp = ft_strjoin(RED, *user);
	else
		tmp = ft_strjoin(BLUE, *user);
	ft_matrixfree(&user);
	return (tmp);
}

static char	*get_os(t_data *mish)
{
	char	**os;
	char	*tmp;
	char	**env;

	os = NULL;
	tmp = NULL;
	env = hashmap_to_matrix(mish->env, &env, 0, 0);
	exec(&os, "/usr/bin/uname", "uname", env);
	ft_matrixfree(&env);
	if (!os)
		os = ft_extend_matrix(os, "Linux");
	if (!ft_strncmp(os[0], "Linux", 5))
		tmp = ft_strjoin(WHITE, "");
	else if (!ft_strncmp(os[0], "Darwin", 6))
		tmp = ft_strjoin(WHITE, "");
	else
		tmp = ft_strjoin(WHITE, "󰖳");
	ft_matrixfree(&os);
	return (tmp);
}

static char	*get_cd(t_data *mish)
{
	char	*home;
	char	*pwd;
	char	*tmp;

	pwd = ft_strdup(hashmap_search(mish->env, "PWD"));
	if (!pwd)
		pwd = ft_strdup("/");
	home = hashmap_search(mish->env, "HOME");
	if (home && home[0] && ft_strnstr(pwd, home, ft_strlen(pwd)))
	{
		tmp = pwd;
		pwd = ft_strjoin("~", &tmp[ft_strlen(home)]);
		free(tmp);
	}
	home = ft_strjoin_var(6, MAGENTA, " 󰝰 ", pwd, DEFAULT, BLACK, "");
	free(pwd);
	return (home);
}

static char	*create_prompt(t_data *mish)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = get_os(mish);
	tmp2 = get_user_and_uid(mish);
	tmp3 = ft_strjoin_var(9, BLACK, "", BBLACK, tmp, "  ", tmp2,
			"@mish󰄛", WHITE, " ");
	free(tmp);
	free(tmp2);
	tmp2 = get_cd(mish);
	if (mish->exit_status == 0)
		tmp = ft_strjoin(tmp2, GREEN);
	else
		tmp = ft_strjoin(tmp2, RED);
	free(tmp2);
	tmp2 = ft_strjoin_var(4, tmp3, tmp, "$> ", DEFAULT);
	free(tmp3);
	free(tmp);
	return (tmp2);
}

char	*init_prompt(t_data *mish)
{
	char	*prompt;
	char	*line;

	prompt = create_prompt(mish);
	line = readline(prompt);
	free(prompt);
	if (!line)
	{
		printf("exit\n");
		return (NULL);
	}
	if (line[0] != '\0')
	{
		add_mish_history(mish, line);
		add_history(line);
	}
	return (line);
}
