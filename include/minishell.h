/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:22:24 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/08 15:46:33 by jmigoya-         ###   ########.fr       */
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

typedef struct s_scmd
{
	char			*full_cmd;
	char			*path;
	// we might still need pointer to builtin function here
	int				in_fd;
	int				out_fd;
	struct s_scmd	*next;
}			t_scmd;

typedef struct s_data
{
	char			*line; // store the line from readline()
	char			**envp;
	struct s_scmd	*scmds;
	char			*pwd;
	char			*old_pwd;
}	t_data;

// WARNING: test:
void	init_promt(char *str);
// singals.c
void	config_signals();
#endif
