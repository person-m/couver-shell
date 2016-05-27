##
## Makefile for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/couvrc/
##
## Made by Melvin Personnier
## Login   <person_m@epitech.eu>
##
## Started on  Wed May 25 18:35:21 2016 Melvin Personnier
## Last update Wed May 25 18:46:35 2016 Melvin Personnier
##

SRC	= ../history/get_next_line.c \
	  couvrc.c \
	  ../minishell1/misc.c \
	  ../minishell1/utils.c \

OBJ	= $(SRC:.c=.o)

NAME	= couvrc

CFLAGS	= -Wall -g -Wextra -W -pedantic

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all
