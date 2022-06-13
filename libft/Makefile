# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: henkaoua <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 17:24:34 by henkaoua          #+#    #+#              #
#    Updated: 2022/04/10 22:35:51 by henkaoua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_isascii.c	\
			ft_memcpy.c		\
			ft_putstr_fd.c	\
			ft_strlcat.c	\
			ft_strrchr.c	\
			ft_atoi.c		\
			ft_isdigit.c	\
			ft_memmove.c	\
			ft_split.c		\
			ft_strlcpy.c	\
			ft_strtrim.c	\
			ft_bzero.c		\
			ft_isprint.c	\
			ft_memset.c		\
			ft_strchr.c		\
			ft_strlen.c		\
			ft_substr.c		\
			ft_calloc.c		\
			ft_itoa.c		\
			ft_putchar_fd.c	\
			ft_strdup.c		\
			ft_strmapi.c	\
			ft_tolower.c	\
			ft_isalnum.c	\
			ft_memchr.c		\
			ft_putendl_fd.c	\
			ft_striteri.c	\
			ft_strncmp.c	\
			ft_toupper.c	\
			ft_isalpha.c	\
			ft_memcmp.c		\
			ft_putnbr_fd.c	\
			ft_strjoin.c	\
			ft_strnstr.c	

BNS_SRCS =	ft_lstnew.c			\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c

NAME	= libft.a
FLGS	= -Wall -Wextra -Werror
OBJS	= ${SRCS:.c=.o}
B_OBJS	= ${BNS_SRCS:.c=.o}
GCC		= gcc
RM		= rm -f
AR		= ar rc
RAN		= ranlib

all:		${NAME}

.c.o:
			${GCC} ${FLGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${AR} ${NAME} ${OBJS}
			${RAN} ${NAME}

bonus:		${OBJS} ${B_OBJS}
			${AR} ${NAME} ${OBJS} ${B_OBJS}
			${RAN} ${NAME}

clean:
			${RM} ${OBJS} ${B_OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all fclean clean re
