# 42SH

42sh is a shell written in C.

## Installation

To install 42sh, run the following commands:

    $ git clone git@github.com:DoctorPok42/42sh.git

    $ cd 42sh

    $ make

    & ./42sh

## Usage

42sh is a shell that can execute commands, manage the environment, and manage the return value of the last command executed.

## Tech

- C

## Folder Structure

```bash
.
├── include
│   ├── lists.h
│   └── mysh.h
├── Makefile
├── README.md
└── src
    ├── builtins
    │   ├── cd.c
    │   ├── env.c
    │   ├── exit.c
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
    │   ├── setenv.c
    │   └── unsetenv.c
    ├── check_github.c
    ├── functions
    │   ├── my_len.c
    │   ├── my_putchar.c
    │   ├── my_put_nbr.c
    │   ├── my_putstr.c
    │   ├── my_strcat.c
    │   ├── my_strcmp.c
    │   ├── my_str_isalpha.c
    │   ├── my_strncmp.c
    │   └── my_str_to_word_array.c
    ├── lists
    │   ├── env.c
    │   ├── parser.c
    │   └── put_in_args.c
    ├── main.c
    ├── mysh_functions.c
    └── utils
        ├── errors.c
        ├── exec
        │   ├── default.c
        │   ├── file.c
        │   ├── pipe.c
        │   └── redirection.c
        ├── execute.c
        ├── get.c
        └── parsing.c
```
