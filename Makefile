##
## Makefile for  in /home/buffat_b/42sh_tmp
## 
## Made by 
## Login   <buffat_b@epitech.net>
## 
## Started on  Fri May 13 21:45:10 2016 
## Last update Mon May 23 20:51:31 2016 
##

NAME	=	42sh

SRC	=	src/main.c \
		src/prompt/init_prompt.c \
		src/prompt/prompt.c \
		src/prompt/cursor.c \
		src/prompt/edit_buffer.c \
		src/prompt/set_term.c \
		src/prompt/annex.c \

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I./include/

CC	=	gcc -Wall -Wextra -Werror


all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) -lncurses

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean	all

aa:	all	clean
	`clean`
