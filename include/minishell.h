/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:22:24 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/09 18:21:00 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

# define ERROR -1
# define FAILURE 1
# define SUCCESS 0

typedef struct s_hash_item
{
	char				*key;
	char				*value;
	struct s_hash_item	*next;
}				t_hash_item;

typedef struct s_hashmap
{
	t_hash_item		**items;
	unsigned int	size;
	unsigned int	count;
}					t_hashmap;

typedef struct s_scmd
{
	char	**full_cmd;
	char	*path;
	int		in_fd;
	int		out_fd;
}			t_scmd;

typedef struct s_data
{
	t_list			*line;
	t_hashmap		*env;
	struct s_scmd	*scmds;
	char			*pwd;
	char			*old_pwd;
	pid_t			pid;
}					t_data;

// WARNING: test:
void	init_promt(char *str);
// singals.c
void	config_signals(void);
#endif
