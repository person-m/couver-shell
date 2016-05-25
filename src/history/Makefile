##
## Makefile for Makefile in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
##
## Made by Melvin Personnier
## Login   <person_m@epitech.eu>
##
## Started on  Wed May 18 15:34:23 2016 Melvin Personnier
<<<<<<< HEAD
## Last update Wed May 25 22:17:18 2016 
##

SRC	= get_next_line.c \
	history_gestion.c \
=======
## Last update Wed May 25 16:30:05 2016 vincent riamon
##

SRC	= get_next_line.c \
	  history_gestion.c \
>>>>>>> e3ae41b785742340ed866467d747a10168cf54ec
	  ../minishell1/misc.c \
	  ../minishell1/utils.c \
	  ../minishell1/builtin.c \

OBJ	= $(SRC:.c=.o)

NAME	= history

CFLAGS	= -Wall -g #-Wextra -W -pedantic

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all
