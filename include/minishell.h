/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:22:24 by migmanu           #+#    #+#             */
/*   Updated: 2023/11/24 13:52:17 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define WRITE_END 1
# define READ_END 0

# define DEFAULT "\001\033[0;39m\002"
# define GRAY "\001\033[1;90m\002"
# define BLACK "\001\033[0;30m\002"
# define RED "\001\033[1;91m\002"
# define GREEN "\001\033[1;92m\002"
# define YELLOW "\001\033[1;93m\002"
# define BLUE "\001\033[1;94m\002"
# define MAGENTA "\001\033[1;95m\002"
# define CYAN "\001\033[1;96m\002"
# define WHITE "\001\033[1;97m\002"

# define RESET "\001\033[0m\002"
# define BGRAY "\001\033[0;100m\002"
# define BBLACK "\001\033[40m\002"
# define BRED "\001\033[0;101m\002"
# define BGREEN "\001\033[0;102m\002"
# define BYELLOW "\001\033[0;103m\002"
# define BBLUE "\001\033[0;104m\002"
# define BMAGENTA "\001\033[0;105m\002"
# define BCYAN "\001\033[0;9106m\002"
# define BWHITE "\001\033[0;107m\002"

# define NOT_EXIT 0
# define IS_EXIT 1

enum e_mish_err
{
	SUCCESS,
	FAILURE,
	ERROR,
	INV_ARGS,
	FORK_ERR,
	PIPE_ERR,
	UNQUOTE,
	NO_PERM = 126,
	NO_FILE = 127,
};

typedef struct s_hash_item
{
	char				*key;
	char				*value;
	int					custom;
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

extern int	g_exit_status;

// MISH
// utils.c
char				*ft_strjoin_var(unsigned int arg_size, ...);
char				**hashmap_to_matrix(t_hashmap *env, char ***matrix,
						unsigned int i, unsigned int j);
void				exec(char	***var, char *path, char *cmd, char **env);
// hashmap
unsigned long int	hash(char *key, unsigned int size);
t_hash_item			*hashmap_create_item(char *key, char *value, int custom);
t_hashmap			*hashmap_create_table(unsigned int size);
void				hashmap_free_item(t_hash_item *item);
void				hashmap_delete(t_hashmap *table, char *key);
void				hashmap_free_table(t_hashmap *table);
void				hashmap_handle_collision(t_hashmap *table, \
		unsigned long int index, t_hash_item *new_item);
void				hashmap_insert(char *key, char *value, \
					t_hashmap *table, int custom);
char				*hashmap_search(t_hashmap *table, char *key);
void				hashmap_print_table(t_hashmap *table, int only_customs);

// input_handler
void				*input_handler(char *line, t_data *mish);
// tokenizer_utils
char				**split_in_words(char *str, char *set);
char				**split_subwords(const char *str, char *set);
char				**insert_subwords(char ***mtx, char **new_items, int pos);
// expander_utils
char				*expand_home(char *str, int i, int quotes[2], char *home);
char				*expand_vars(t_data *mish, char *str, int quotes[2], int i);
// utils.c
int					count_subwords(char *s, char *set, int count);
int					count_words(const char *str, char *set, int cts[2]);
int					find_inset(const char *str, char *set);
// syntax_list_utils.c
char				**trim_all(char **tokens);
char				*get_trimmed_str(char *str);
int					len_noquotes(char *str);
t_scmd				*init_node(void);
t_list				*clean_fail(t_list *cmds, char **tokens, char **tmp);
// get_node.c
t_scmd				*get_node(t_scmd *node, char **cmds[2], int *i);
// redirections.c
t_scmd				*redir_in(t_scmd *node, char **cmds, int *i);
t_scmd				*redir_in_heredoc(t_scmd *node, char **cmds, int *i);
t_scmd				*redir_out(t_scmd *node, char **cmds, int *i);
t_scmd				*redir_out_append(t_scmd *node, char **cmds, int *i);
// redirections_utils.c
int					get_heredoc_fd(char *limit);
int					get_fd(int oldfd, char *path, int flags[2]);

// exit
void				mish_error(t_data *mish, char *param, int err, int is_exit);
void				handle_exit(t_data *mish, char *param, \
					int err, int is_exit);
void				clean_and_exit(t_data *mish);
void				ft_matrixfree(char ***matrix);
void				free_scmd(void *content);

// init
char				*init_prompt(t_data *mish);
void				init_mish(t_data *mish, char *argv[], char *envp[]);
t_hashmap			*env_to_hash(char **env);

// singals.c
void				config_signals(void);

// executor
void				executor(t_data *mish);
char				*get_path(t_data *mish, char *cmd);
void				set_file_descriptors(t_data *mish, int fds[2], int *c);
char				*get_cmd_path(char *cmd, char *env[]);
void				dup_cmd(t_scmd *cmd);

// testing
void				create_mock_mish(t_data *mish, char *line);

// builtins
int					check_if_builtin(const char *str);
int					builtins_router(t_data *mish, t_scmd cmd, int if_exit);
int					ft_chr_pos(const char *str, const char c);
void				mish_exit(t_data *mish, t_scmd cmd);
void				mish_pwd(t_data *mish, t_scmd cmd, int if_exit);
void				mish_cd(t_data *mish, t_scmd cmd, int if_exit);
void				mish_export(t_data *mish, t_scmd cmd, int if_exit);
void				mish_unset(t_data *mish, t_scmd cmd, int if_exit);
void				mish_echo(t_data *mish, t_scmd cmd, int if_exit);
void				mish_env(t_data *mish, t_scmd cmd, int if_exit);

#endif
