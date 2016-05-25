##
## Makefile for Makefile in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
##
## Made by Melvin Personnier
## Login   <person_m@epitech.eu>
##
## Started on  Wed May 18 15:34:23 2016 Melvin Personnier
## Last update Tue May 24 16:42:56 2016 Melvin Personnier
##

SRC	= main.c \
	  misc.c \
	  builtin.c \
	  builtin2.c \
	  builtin3.c \
	  utils.c \
	  tab_ptn_fct.c \
	  exec_sh1.c \
	  my_str_to_wordtab_pattern.c \
	  cd.c \
	  ../history/history_gestion.c \
	  ../history/get_next_line.c

OBJ	= $(SRC:.c=.o)

NAME	= sh1

CFLAGS	= -Wall -g -Wextra -W -pedantic -I../../include/

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all
