SRCS =	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c	\
		ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c	\
		ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c	\
		ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strdup.c ft_calloc.c	\
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c		\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c

BONUS =	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c	\
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c	\
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c 		\
		ft_strndup.c lib_utils.c get_next_line.c get_next_line_utils.c	\
		ft_how_many_char.c ft_abs.c ft_strcmp.c dop_func.c

SRCS_DIR = srcs/

OBJS = ${addprefix ${SRCS_DIR}, ${SRCS:.c=.o}}

BONUS_OBJS = ${addprefix ${SRCS_DIR}, ${BONUS:.c=.o}}

NAME = libft.a

HEADER = libft.h

CC = gcc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

.c.o:		${HEADER}
			${CC} ${CFLAGS} -I. -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${BONUS_OBJS} ${HEADER}
			ar rcs ${NAME} ${OBJS} ${BONUS_OBJS} $?

bonus:		${OBJS} ${BONUS_OBJS} ${HEADER}
			ar rcs ${NAME} ${OBJS} ${BONUS_OBJS} $?

all:		${NAME}

clean:		
			${RM} ${OBJS} ${BONUS_OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all
