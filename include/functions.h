/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 20:38:10 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/11/24 15:21:31 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structs.h"

char				*init_prompt(t_data *mish);
// init_mish.c
void				init_mish(t_data *mish, char *argv[], char *envp[]);
// env_to_hash.c
t_hashmap			*env_to_hash(char **env);
// utils.c
char				*ft_strjoin_var(unsigned int arg_size, ...);
char				**hashmap_to_matrix(t_hashmap *env, char ***matrix,
						unsigned int i, unsigned int j);
void				exec(char	***var, char *path, char *cmd, char **env);

// HASHMAP
unsigned long int	hash(char *key, unsigned int size);
t_hash_item			*hashmap_create_item(char *key, char *value, int custom);
t_hashmap			*hashmap_create_table(unsigned int size);
void				hashmap_free_item(t_hash_item *item);
int					hashmap_delete(t_hashmap *table, char *key);
void				hashmap_free_table(t_hashmap *table);
void				hashmap_handle_collision(t_hashmap *table, \
		unsigned long int index, t_hash_item *new_item);
t_hash_item			*hashmap_insert(char *key, char *value, \
					   t_hashmap *table, int custom);
char				*hashmap_search(t_hashmap *table, char *key);
void				hashmap_print_table(t_hashmap *table, int only_customs);

// INPUT_HANDLER
// input_handler.c
void				*input_handler(char *line, t_data *mish);
// tokenizer_utils.c
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

// HANDLE_EXIT
// handle_exit.c
void				handle_exit(t_data *mish, char *param,
						int err, int is_exit);
void				free_scmd(void *content);

// SIGNALS
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
