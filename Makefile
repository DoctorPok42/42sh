##
## EPITECH PROJECT, 2023
## navy
## File description:
## Makefile
##

SRC = src/main.c \
	src/mysh_functions.c \
	src/utils/get.c \
	src/utils/parsing.c \
	src/utils/errors.c \
	src/utils/execute.c \
	src/utils/exec/default.c \
	src/utils/exec/pipe.c \
	src/utils/exec/redirection.c \
	src/utils/exec/file.c \
	src/builtins/cd.c \
	src/builtins/env.c \
	src/builtins/exit.c \
	src/builtins/setenv.c \
	src/builtins/unsetenv.c \
	src/lists/parser.c \
	src/lists/put_in_args.c \
	src/lists/env.c \
	src/functions/my_putstr.c \
	src/functions/my_strcmp.c \
	src/functions/my_strncmp.c \
	src/functions/my_len.c \
	src/functions/my_strcat.c \
	src/functions/my_str_isalpha.c \
	src/functions/my_str_to_word_array.c \
	src/functions/my_put_nbr.c \
	src/functions/my_putchar.c

OBJ = $(SRC:.c=.o)

CFLAGS = -I include/ -Wall -Wextra

NAME = mysh

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
