/*
** shell.h for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:50:52 2016
** Last update Thu May 26 15:59:44 2016 
*/

#ifndef SHELL_H_
# define SHELL_H_

/*
**	Libraries
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "prompt.h"

typedef struct	s_shell
{
  char		**env;
  char		**alias;
  char		**history;
  int		size_hist;
  int		ret;
  t_prompt	*prompt;
}		t_shell;

char		**cpy_env(char **env);
char		**my_str_to_wordtab_pattern(char *s, char *pattern);
int		minishell1(char **tab, t_shell *sh);
int		is_a_builtin(char *str);
void		free_tab(char **tab);
void		create_alias(t_shell *sh);
void		create_oldpwd(t_shell *sh);
void		fill_history(t_shell *sh);
void		update_history(char **cmd, t_shell *sh);
void		the_execution(char **cmd, t_shell *sh);

char		*get_var_env(char **, char *);

void            loop_prompt(t_shell *);

void		signal_handler(void);
void		check_signals(t_shell *);
void		exit_shell(t_shell *, int);

char		**lexer(char *line);
int		check_command(char **command);

#endif /* !SHELL_H_ */
