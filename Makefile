##
## Makefile for  in /home/buffat_b/couver-shell
##
## Made by
## Login   <buffat_b@epitech.net>
##
## Started on  Wed May 25 00:12:22 2016
## Last update Fri Jun  3 00:12:09 2016 vincent riamon
##

NAME	=	42sh

SRC	=	src/main.c \
		src/prompt/prompt.c \
		src/prompt/init_prompt.c \
		src/prompt/aff_prompt.c \
		src/prompt/manage_prompt.c \
		src/prompt/fct_prompt/cursor.c \
		src/prompt/fct_prompt/edit_buffer.c \
		src/prompt/fct_prompt/set_term.c \
		src/prompt/fct_prompt/get_cursor_pos.c \
		src/prompt/fct_prompt/fct_prompt.c \
		src/prompt/fct_prompt/bltin_rebind.c \
		src/prompt/auto_completion/auto_complet.c \
		src/prompt/auto_completion/bltin_completion.c \
		src/prompt/auto_completion/bltin_completion_command.c \
		src/prompt/auto_completion/fct_completions.c \
		src/prompt/auto_completion/list_completion.c \
		src/minishell1/misc.c \
		src/minishell1/builtin.c \
		src/minishell1/builtin2.c \
		src/minishell1/builtin3.c \
		src/minishell1/builtin4.c \
		src/minishell1/builtin5.c \
		src/minishell1/builtin6.c \
		src/minishell1/utils.c \
		src/minishell1/tab_ptn_fct.c \
		src/minishell1/my_str_to_wordtab_pattern.c \
		src/minishell1/cd.c \
		src/minishell1/exec_sh1.c \
		src/minishell2/minishell2.c \
		src/minishell2/pars.c \
		src/minishell2/pipe.c \
		src/minishell2/redirections.c \
		src/minishell2/verif_return.c \
		src/minishell2/verifs.c \
		src/minishell2/inhibitors.c \
		src/history/history_gestion.c \
		src/history/get_next_line.c \
		src/couvrc/couvrc.c \
		src/lexer/lexer.c \
		src/parser/check_command.c \
		src/parser/check_identity.c \
		src/parser/replace_exclam.c \
		src/parser/replace_dollar.c \
		src/parser/misc_replace.c \
		src/parser/misc_replace2.c \
		src/globbing/globbing.c \
		src/annex_main/get_std_input.c \
		src/annex_main/signals.c \
		src/minishell1/logo.c \
		src/backquote/backquote.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I./include/

CC	=	cc -Wall -Wextra -Werror -g


all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) -lncurses

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean	all

aa:	all	clean
