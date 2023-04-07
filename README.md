# MYSH 2

MYSH is a shell written in C.

## Installation

To install MYSH, run the following commands:

    $ git clone git@github.com:EpitechPromo2027/B-PSU-200-BDX-2-1-minishell2-remi.mazat.git

    $ cd B-PSU-200-BDX-2-1-minishell2-remi.mazat

    $ make

    & ./mysh

## Usage

MYSH is a shell that can execute commands, manage the environment, and manage the return value of the last command executed.

## Tech

- C

## Folder Structure

```css
.
├── include
│   ├── lists.h
│   └── mysh.h
├── Makefile
├── README.md
├── src
│   ├── builtins
│   │   ├── cd.c
│   │   ├── env.c
│   │   ├── exit.c
│   │   ├── setenv.c
│   │   └── unsetenv.c
│   ├── functions
│   │   ├── my_len.c
│   │   ├── my_putchar.c
│   │   ├── my_put_nbr.c
│   │   ├── my_putstr.c
│   │   ├── my_strcat.c
│   │   ├── my_strcmp.c
│   │   ├── my_str_isalpha.c
│   │   ├── my_strncmp.c
│   │   └── my_str_to_word_array.c
│   ├── lists
│   │   ├── env.c
│   │   ├── parser.c
│   │   └── put_in_args.c
│   ├── main.c
│   ├── mysh_functions.c
│   └── utils
│       ├── errors.c
│       ├── exec
│       │   ├── default.c
│       │   ├── pipe.c
│       │   └── redirection.c
│       ├── execute.c
│       ├── get.c
└──     └── parsing.c
```