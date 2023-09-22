#Name
NAME:=minishell

#Compiler
CC=	cc
CFLAGS=	-Wall -Werror -Wextra -Iinclude -g

#Libft
LIBFT_DIR:=./src/libft
LIBFT:=./src/libft/libft.a

#Directories
SRC_DIR:=src
OBJ_DIR:=obj

#Source files
SRC:=${SRC_DIR}/init.c \
	${SRC_DIR}/errors.c \
	${SRC_DIR}/main.c \
	${SRC_DIR}/exec/pipes.c \
	${SRC_DIR}/exec/utils.c \
	${SRC_DIR}/exec/redirections.c \
	${SRC_DIR}/exec/redirection_utils.c \
	${SRC_DIR}/exec/exec.c \
	${SRC_DIR}/exec/cmd_utils.c \
	${SRC_DIR}/exec/fork.c \
	${SRC_DIR}/exec/free.c \
	${SRC_DIR}/exec/path.c	\
	${SRC_DIR}/exec/path_utils.c	\
	${SRC_DIR}/exec/signals.c	\
	${SRC_DIR}/parsing/analyse_delimiters.c \
	${SRC_DIR}/parsing/analyse_words.c \
	${SRC_DIR}/parsing/parsing_utils.c \
	${SRC_DIR}/parsing/quotes.c \
	${SRC_DIR}/parsing/tokenize.c \
	${SRC_DIR}/parsing/expand_exit.c \
	${SRC_DIR}/parsing/expand_utils.c \
	${SRC_DIR}/parsing/expand_var.c \
	${SRC_DIR}/parsing/expand.c \
	${SRC_DIR}/parsing/heredoc_utils.c \
	${SRC_DIR}/parsing/heredoc.c \
	${SRC_DIR}/parsing/tokens_utils.c \
	${SRC_DIR}/parsing/var.c \
	${SRC_DIR}/builtins/builtins.c \
	${SRC_DIR}/builtins/directory_utils.c \
	${SRC_DIR}/builtins/env.c \
	${SRC_DIR}/builtins/ft_cd.c \
	${SRC_DIR}/builtins/export.c \
	${SRC_DIR}/builtins/builtin_utils.c \
	${SRC_DIR}/builtins/unset.c \
	${SRC_DIR}/builtins/exit.c \
	${SRC_DIR}/builtins/export_utils.c

#Object files
OBJ:=${patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC)} 

#Rules
${NAME}: ${OBJ} include/minishell.h include/parsing.h include/builtins.h
	$(MAKE) -C $(LIBFT_DIR)
	${CC} ${CFLAGS} ${OBJ} ${LIBFT} -o ${NAME} -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: ${NAME}

clean:
	rm -rf ${OBJ_DIR}
	${MAKE} clean -C ${LIBFT_DIR}

fclean: clean
	rm -f ${NAME}
	${MAKE} fclean -C ${LIBFT_DIR}

re: fclean all

.PHONY: re	fclean	clean	all
