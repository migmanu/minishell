/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migmanu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:22:24 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/08 21:53:51 by sebasnadu        ###   ########.fr       */
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
}			t_hash_item;

typedef struct s_hashmap
{
	t_hash_item		**items;
	unsigned int	size;
	unsigned int	count;
}				t_hashmap;

typedef struct s_scmd
{
	char	**full_cmd;
	char	*path;		
	int		in_fd;
	int		out_fd;
}				t_scmd;

typedef struct s_data
{
	t_list		*cmds;
	t_hashmap	*env;
	pid_t		pid;
}				t_data;

// hashmap
unsigned long int	hash(char *key, unsigned int size);
t_hash_item			*hashmap_create_item(char *key, char *value);
t_hashmap			*hashmap_create_table(unsigned int size);
void				hashmap_free_item(t_hash_item *item);
void				hashmap_delete(t_hashmap *table, char *key);
void				hashmap_free_table(t_hashmap *table);
void				hashmap_handle_collision(t_hashmap *table, \
							unsigned long int index, t_hash_item *new_item);
void				hashmap_insert(char *key, char *value, t_hashmap *table);
char				*hashmap_search(t_hashmap *table, char *key);
void				hashmap_print_table(t_hashmap *table);

// input_handler.c
void				*input_handler(char *line, t_data *mish);

// init
void				init_prompt(t_data *mish);
void				init_mish(t_data *mish, char *envp[]);
t_hashmap			*env_to_hash(char **env);
// singals.c
void				config_signals();

#endif
