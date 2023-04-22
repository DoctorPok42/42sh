##
## EPITECH PROJECT, 2023
## navy
## File description:
## Makefile
##

SRC = src/main.c \
	src/mysh_functions.c \
	src/check_github.c \
	src/parse.c \
	src/diplay_prompt.c \
	$(addprefix src/utils/, \
		get.c \
		parsing.c \
		errors.c \
		exec/default.c \
		exec/pipe.c \
		exec/redirection.c \
		exec/file.c \
	) \
	$(addprefix src/builtins/, \
		cd.c \
		env.c \
		exit.c \
		setenv.c \
		unsetenv.c \
		history.c \
		alias.c \
		unalias.c \
	) \
	$(addprefix src/lists/, \
		parser.c \
		put_in_args.c \
		env.c \
	) \
	$(addprefix src/functions/, \
		my_putstr.c \
		my_strcmp.c \
		my_strncmp.c \
		my_len.c \
		my_strcat.c \
		my_str_isalpha.c \
		my_str_to_word_array.c \
		my_put_nbr.c \
		my_putchar.c \
	)

OBJ = $(SRC:.c=.o)

CFLAGS = -I include/ -Wall -Wextra

NAME = 42sh

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
