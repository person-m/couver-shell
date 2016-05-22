##
## Makefile for Makefile in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
##
## Made by Melvin Personnier
## Login   <person_m@epitech.eu>
##
## Started on  Wed May 18 15:34:23 2016 Melvin Personnier
## Last update Sun May 22 10:36:13 2016 vincent riamon
##

SRC	= get_next_line.c \
	  fill_history.c \
	  ../minishell1/misc.c \
	  ../minishell1/utils.c \

OBJ	= $(SRC:.c=.o)

NAME	= history

CFLAGS	= -Wall -g -Wextra -W -pedantic

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all
