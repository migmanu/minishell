# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: migmanu <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 19:24:44 by migmanu           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/11/15 18:27:55 by sebasnadu        ###   ########.fr        #
=======
#    Updated: 2023/11/13 12:43:08 by jmigoya-         ###   ########.fr        #
>>>>>>> upstream/main
#                                                                              #
# **************************************************************************** #

# SOURCES
SRCS_DIR = ./src
SRCS = $(wildcard $(SRCS_DIR)/*/*.c)
SRCS += $(wildcard $(SRCS_DIR)/main.c)

OBJ_FILES = $(patsubst %.c, %.o, $(SRCS))

#LIBFT
LIBFT_DIR = ./libft
LIBFT_PATH = $(LIBFT_DIR)/libft.a
READLINE_MAC_PATH = /opt/homebrew/opt/readline

#LIBRARIES
ifeq ($(shell uname), Darwin)
	INCLUDE_DIRS = -I ./include -I$(LIBFT_DIR) -I$(READLINE_MAC_PATH)/include
	LDFLAGS = -lreadline \
			  -L$(READLINE_MAC_PATH)/lib -L$(LIBFT_DIR) -lft
else
	INCLUDE_DIRS = -I ./include -I $(LIBFT_DIR)
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
	@make bonus -C $(LIBFT_DIR) -s

%.o: %.c
	@git submodule update --init -q
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo $(RED) "Cleaning..." $(EOC)
	@make clean -C $(LIBFT_DIR) -s
	@$(RM) $(OBJ_FILES)

fclean: clean
	@echo $(PURPLE) "Full Cleaning...🧹" $(EOC)
	@make fclean -C $(LIBFT_DIR) -s
	@$(RM) $(NAME)

re: fclean all
	@git submodule update --remote -q

.PHONY: all test clean fclean
