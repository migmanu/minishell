# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: migmanu <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 19:24:44 by migmanu           #+#    #+#              #
#    Updated: 2023/12/09 13:44:29 by jmigoya-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SOURCES
SRCS_DIR = ./src/
FILES = mish/main.c mish/init_mish.c mish/init_prompt.c mish/inits_utils.c \
       mish/utils.c builtins/builtins_router.c  \
       builtins/mish_cd.c builtins/mish_env.c builtins/mish_export.c \
       builtins/mish_pwd.c builtins/builtins_utils.c builtins/mish_echo.c \
       builtins/mish_exit.c builtins/mish_history.c builtins/mish_unset.c \
       executor/executor.c executor/executor_utils.c \
       handle_exit/handle_exit.c handle_exit/handle_exit_utils.c \
       hashmap/hash_algo.c hashmap/hashmap_free_item.c \
       hashmap/hashmap_print_table.c hashmap/hashmap_create_item.c \
       hashmap/hashmap_free_table.c hashmap/hashmap_search.c \
       hashmap/hashmap_create_table.c hashmap/hashmap_handle_collision.c \
       hashmap/hashmap_search_key.c hashmap/hashmap_delete.c \
       hashmap/hashmap_insert.c \
       input_handler/expander_utils.c input_handler/input_handler.c \
       input_handler/redirections_utils.c input_handler/tokenizer_utils.c \
       input_handler/get_node.c input_handler/redirections.c \
       input_handler/syntax_list_utils.c input_handler/utils.c \
       signals/signals.c

SRCS = $(addprefix $(SRCS_DIR), $(FILES))

OBJ_DIR = ./obj/
OBJ_FILES = $(patsubst $(SRCS_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

#LIBFT
LIBFT_DIR = ./libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a
READLINE_MAC_PATH = /opt/homebrew/opt/readline

#LIBRARIES
ifeq ($(shell uname), Darwin)
	INCLUDE_DIRS = -I ./include -I$(LIBFT_DIR)/includes \
				   -I$(READLINE_MAC_PATH)/include
	LDFLAGS = -lreadline \
			  -L$(READLINE_MAC_PATH)/lib -L$(LIBFT_DIR) -lft
else
	INCLUDE_DIRS = -I ./include -I $(LIBFT_DIR)/includes
	LDFLAGS = -lreadline -lhistory -L$(LIBFT_DIR) -lft
endif

CFLAGS = -Wall -Werror -Wextra -g $(INCLUDE_DIRS)
TFLAGS = -g $(INCLUDE_DIRS)

# COMPILATION
NAME = minishell
CC = cc
RM = rm -f

# COLORS
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"

all: $(NAME)

test: CFLAGS = $(TEST_CFLAGS)
test: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT_PATH)
	@echo $(CYAN) "Compiling $@...🛠️" $(EOC)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LDFLAGS)
	@echo $(GREEN) "OK COMPILED" $(EOC)

$(LIBFT_PATH):
	@make -C $(LIBFT_DIR) -s

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@git submodule update --init -q
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo $(RED) "Cleaning..." $(EOC)
	@make clean -C $(LIBFT_DIR) -s
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@echo $(PURPLE) "Full Cleaning...🧹" $(EOC)
	@make fclean -C $(LIBFT_DIR) -s
	@$(RM) $(NAME)

re: fclean all
	@git submodule update --remote -q

.PHONY: all test clean fclean
