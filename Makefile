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
		$(addsuffix .c, \
			get \
			parsing \
			errors \
			exec/default \
			exec/pipe \
			exec/redirection \
			exec/file \
			exec/index \
		) \
	) \
	$(addprefix src/builtins/, \
		$(addsuffix .c, \
			cd \
			env \
			exit \
			setenv \
			unsetenv \
			history \
			alias \
			unalias \
			system \
			system/help \
			system/battery \
			system/cpu \
			system/memory \
			system/network \
		) \
	) \
	$(addprefix src/lists/, \
		$(addsuffix .c, \
			parser \
			put_in_args \
			env \
		) \
	) \
	$(addprefix src/functions/, \
		$(addsuffix .c, \
			my_putstr \
			my_strcmp \
			my_strncmp \
			my_len \
			my_strcat \
			my_str_isalpha \
			my_str_to_word_array \
			my_put_nbr \
			my_putchar \
		) \
	) \
	$(addprefix src/prompt/, \
		$(addsuffix .c, \
			get_input \
			arrows \
		)\
	) \

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
