# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 16:59:53 by rohoarau          #+#    #+#              #
#    Updated: 2022/05/19 19:54:29 by rohoarau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell
LIBFT 		= 	libft.a
LIB_DIR		=	libft/
OBJ_DIR		=	obj/
SRCS_DIR	=	src/
SRCS		=	main.c				\
				utils.c				\
				2utils.c			\
				temp.c				\
				built_in.c			\
				utils_built_in.c	\
				echo.c				\
				env.c				\
				export.c			\
				unset.c				\
				cd.c				\
				pwd.c				\
				signals.c			\
				init.c				\
				exit.c				\
				pipes.c				\
				redirection.c		\
				minishell.c			\
				cut_space.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

LFLAGS = -I include/
CFLAGS = -Wall -Wextra -Werror
DEBUGGING = -ggdb
LREADLINE = -lreadline
CC = gcc
RM = rm -rf
AR = ar rc

all: $(NAME)

$(OBJ_DIR)%.o : $(SRCS_DIR)%.c
		@mkdir -p $(OBJ_DIR)
		$(CC) -c $(CFLAGS) $(DEBUGGING) $(LFLAGS) $< -o $@

$(NAME): $(OBJS)
		@echo "Compilation of $(OBJ_DIR):  \033[1;32mOK\033[m\n"
		make -C $(LIB_DIR)
		@echo "Compilation of $(LIB_DIR):  \033[1;32mOK\033[m\n"
		$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(LIB_DIR)$(LIBFT) -o $(NAME) -lreadline -L $(HOME)/.brew/opt/readline/lib -I $(HOME)/.brew/opt/readline/include
		@echo "Compilation of $(NAME):  \033[1;32mOK\033[m\n"
		clear
		@echo "\033[1;31m$$HEADER\033[m"

clean:
		$(RM) $(OBJ_DIR)
		$(RM) $(OBJS)
		make -C $(LIB_DIR) clean
		@echo "\033[1;31mObjects removed\033[m"

fclean: clean
		$(RM) $(NAME)
		make -C $(LIB_DIR) fclean
		@echo "\033[1;31m$(NAME) && $(LIB_DIR) removed\033[m"

re: fclean all

define HEADER
.-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-.
.                                        		  .
:	        _      _    _        _ _		  :
| 	  _ __ (_)_ _ (_)__| |_  ___| | |		  |
!	 | '  \| | ' \| (_-< ' \/ -_) | |		  !
|	 |_|_|_|_|_||_|_/__/_||_\___|_|_|		  |
:			  by henkaoua && rohoarau	  :
:            		  run ./minishell       	  :
`-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-'
                                
endef
export HEADER

.PHONY: all clean re fclean
