##
## Makefile for Makefile in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
##
## Made by Melvin Personnier
## Login   <person_m@epitech.eu>
##
## Started on  Wed May 18 15:34:23 2016 Melvin Personnier
## Last update Wed May 18 15:36:52 2016 Melvin Personnier
##

SRC	= main.c \

OBJ	= $(SRC:.c=.o)

NAME	= sh1

CFLAGS	= -Wall -Wextra -W -pedantic

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all
