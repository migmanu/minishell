/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:34:46 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/24 12:33:01 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

enum e_mish_err
{
	SUCCESS,
	FAILURE,
	ERROR,
	INV_ARGS,
	FORK_ERR,
	PIPE_ERR,
	UNQUOTE,
	HASH_FULL,
	NO_PERM = 126,
	NO_FILE = 127,
};

typedef struct s_hash_item
{
	char				*key;
	char				*value;
	struct s_hash_item	*next;
}	t_hash_item;

typedef struct s_hashmap
{
	t_hash_item		**items;
	unsigned int	size;
	unsigned int	count;
}	t_hashmap;

typedef struct s_scmd
{
	char	**full_cmd;
	char	*path;
	int		in_fd;
	int		out_fd;
}	t_scmd;

typedef struct s_data {
	t_list		*cmds;
	t_hashmap	*env;
	pid_t		pid;
	pid_t		*pids;
	char		*old_pwd;
}	t_data;

int	g_exit_status;

#endif
