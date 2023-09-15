NAME = libft.a
SRC_DIR:=src
OBJ_DIR:=obj
SRC=${SRC_DIR}/ascii/ft_isalnum.c	\
	${SRC_DIR}/ascii/ft_isalpha.c	\
	${SRC_DIR}/ascii/ft_isascii.c	\
	${SRC_DIR}/ascii/ft_isdigit.c	\
	${SRC_DIR}/ascii/ft_isprint.c	\
	${SRC_DIR}/ascii/ft_tolower.c	\
	${SRC_DIR}/ascii/ft_toupper.c	\
	${SRC_DIR}/gnl/get_next_line_utils.c	\
	${SRC_DIR}/gnl/get_next_line.c	\
	${SRC_DIR}/linked_lists/ft_lstadd_back.c	\
	${SRC_DIR}/linked_lists/ft_lstadd_front.c	\
	${SRC_DIR}/linked_lists/ft_lstclear.c	\
	${SRC_DIR}/linked_lists/ft_lstdelone.c	\
	${SRC_DIR}/linked_lists/ft_lstiter.c	\
	${SRC_DIR}/linked_lists/ft_lstlast.c	\
	${SRC_DIR}/linked_lists/ft_lstmap.c	\
	${SRC_DIR}/linked_lists/ft_lstnew.c	\
	${SRC_DIR}/linked_lists/ft_lstsize.c	\
	${SRC_DIR}/memory/ft_bzero.c	\
	${SRC_DIR}/memory/ft_calloc.c	\
	${SRC_DIR}/memory/ft_memchr.c	\
	${SRC_DIR}/memory/ft_memcmp.c	\
	${SRC_DIR}/memory/ft_memcpy.c	\
	${SRC_DIR}/memory/ft_memmove.c	\
	${SRC_DIR}/memory/ft_memset.c	\
	${SRC_DIR}/numbers/ft_atoi.c \
	${SRC_DIR}/numbers/ft_itoa.c	\
	${SRC_DIR}/numbers/ft_putnbr_fd.c	\
	${SRC_DIR}/strings/ft_putchar_fd.c	\
	${SRC_DIR}/strings/ft_putendl_fd.c	\
	${SRC_DIR}/strings/ft_putstr_fd.c	\
	${SRC_DIR}/strings/ft_split.c	\
	${SRC_DIR}/strings/ft_strchr.c	\
	${SRC_DIR}/strings/ft_strdup.c	\
	${SRC_DIR}/strings/ft_striteri.c	\
	${SRC_DIR}/strings/ft_strjoin_free.c \
	${SRC_DIR}/strings/ft_strjoin.c \
	${SRC_DIR}/strings/ft_strlcat.c	\
	${SRC_DIR}/strings/ft_strlcpy.c	\
	${SRC_DIR}/strings/ft_strlen.c \
	${SRC_DIR}/strings/ft_strmapi.c \
	${SRC_DIR}/strings/ft_strncmp.c	\
	${SRC_DIR}/strings/ft_strnstr.c \
	${SRC_DIR}/strings/ft_strrchr.c \
	${SRC_DIR}/strings/ft_strtrim.c \
	${SRC_DIR}/strings/ft_substr.c	\
	${SRC_DIR}/ft_dprintf/ft_dprintf.c	\
	${SRC_DIR}/ft_dprintf/ft_puthex.c	\
	${SRC_DIR}/ft_dprintf/ft_putptr.c	\
	${SRC_DIR}/ft_dprintf/ft_putunsigned.c \
	${SRC_DIR}/ft_dprintf/len_utils.c

OBJ:=${patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC)}

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -Iinclude

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJ}
	ar rcs	${NAME}	${OBJ}

all: ${NAME}

clean : 
	rm -rf	${OBJ_DIR}

fclean :	clean
	rm -f	${NAME}

re:	fclean	all

.PHONY:	re	fclean	clean	all
