##
## Makefile for Makefile in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
##
## Made by Melvin Personnier
## Login   <person_m@epitech.eu>
##
## Started on  Wed May 18 15:34:23 2016 Melvin Personnier
## Last update Thu May 19 13:57:11 2016 vincent riamon
##

SRC	= main.c \
	  misc.c \
	  builtin.c \
	  builtin2.c \
	  utils.c

OBJ	= $(SRC:.c=.o)

NAME	= sh1

CFLAGS	= -Wall -g # -Wextra -W -pedantic

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all
