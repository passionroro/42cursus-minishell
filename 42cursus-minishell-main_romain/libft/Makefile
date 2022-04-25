SRC_DIR		=	./

SRCS		=	ft_atoi.c		\
				ft_itoa.c		\
				ft_bzero.c         \
				ft_isdigit.c     \
				ft_memmove.c     \
				ft_strlcpy.c     \
				ft_isalnum.c     \
				ft_memset.c     \
				ft_strlen.c     \
				ft_isalpha.c     \
				ft_strchr.c     \
				ft_isascii.c     \
				ft_memcpy.c     \
				ft_strlcat.c     \
				ft_strrchr.c    \
				ft_memchr.c		\
				ft_strncmp.c	\
				ft_memcmp.c		\
				ft_strnstr.c	\
				ft_toupper.c	\
				ft_tolower.c	\
				ft_isprint.c	\
				ft_calloc.c		\
				ft_strdup.c		\
				ft_substr.c		\
				ft_strjoin.c	\
				ft_strmapi.c	\
				ft_striteri.c	\
				ft_putchar_fd.c	\
				ft_putstr_fd.c	\
				ft_putendl_fd.c	\
				ft_putnbr_fd.c	\
				ft_strtrim.c	\
				ft_split.c		\

BONUS_SRC	=	ft_lstnew.c		\
				ft_lstadd_front.c	\
				ft_lstadd_back.c	\
				ft_lstlast.c	\
				ft_lstsize.c	\

OBJS        = ${SRCS:.c=.o}

BONUS_OBJS	=	${BONUS_SRC:.c=.o}

NAME        = libft.a

CC            = gcc

CFLAGS        = -Wall -Wextra -Werror

AR_RCS        = ar rcs

all:            ${NAME}

.c.o:
				@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:        ${OBJS}
				@${AR_RCS} ${NAME} ${OBJS}

bonus:			${BONUS_OBJS}
				@${AR_RCS} ${NAME} ${BONUS_OBJS}

clean:
				@rm -f ${OBJS} ${BONUS_OBJS}

fclean:			clean
				@rm -f ${NAME}

re:                fclean all

.PHONY:            all clean fclean re bonus
