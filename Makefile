# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rohoarau <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 16:59:53 by rohoarau          #+#    #+#              #
#    Updated: 2022/04/07 14:13:50 by henkaoua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	minishell
LIBFT 		= 	libft.a
LIB_DIR		=	libft/
OBJ_DIR		=	obj/
SRCS_DIR	=	src/
SRCS		=	main.c				\

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
		make -C $(LIB_DIR)
		@echo "Compilation of $(LIB_DIR):  \033[1;32mOK\033[m"
		@echo ""
		$(CC) $(CFLAGS) $(LREADLINE) $(OBJS) $(LFLAGS) $(LIB_DIR)$(LIBFT) -o $(NAME)
		@echo "Compilation of $(NAME):  \033[1;32mOK\033[m"
		@echo ""

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

.PHONY: all clean re fclean
