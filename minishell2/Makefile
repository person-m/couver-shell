##
## Makefile for 42sh in /home/hedia_m/couver-shell/minishell2
## 
## Made by mohamed-laid hedia
## Login   <hedia_m@epitech.net>
## 
## Started on  Mon May 23 13:09:56 2016 mohamed-laid hedia
## Last update Mon May 23 14:18:50 2016 mohamed-laid hedia
##

SRC	= main.c \
	  minishell2.c \
	  pars.c \
	  pipe.c \
	  redirections.c \
	  verif_return.c \
	  verifs.c \
	  ../history/get_next_line.c \
	  ../minishell1/builtin2.c \
	  ../minishell1/builtin.c \
	  ../minishell1/cd.c \
	  ../minishell1/exec_sh1.c \
	  ../minishell1/misc.c \
	  ../minishell1/my_str_to_wordtab_pattern.c \
	  ../minishell1/utils.c \
	  ../minishell1/tab_ptn_fct.c \


OBJ	= $(SRC:.c=.o)

NAME	= test42

CFLAGS	= -Wall -Wextra -W

$(NAME): $(OBJ)
	cc $(OBJ) -o $(NAME)

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
