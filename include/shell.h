/*
** shell.h for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:50:52 2016
** Last update Mon May 30 17:46:59 2016 vincent riamon
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

void		get_std_input(t_shell *sh);

char		**cpy_env(char **env);
char		**my_str_to_wordtab_pattern(char *s, char *pattern);
int		minishell1(char **tab, t_shell *sh);
int		is_a_builtin(char *str);
int		tab_len(char **tab);
void		aff_tab(char **tab);
void		free_tab(char **tab);
void		create_alias(t_shell *sh);
void		create_oldpwd(t_shell *sh);
void		*my_malloc(int size);
char		*couvrc(char **env);
void		the_execution(char **cmd, t_shell *sh);

void		fill_history(t_shell *sh);
void		update_history(t_shell *sh);
char		*wordtab_in_str(char **tab, int mode);
char		*error_history(char *var, int mode);

int		replace_var_env(char ***cmd, t_shell *sh);
int		replace_exclam_dot(char ***cmd, t_shell *sh);
char		*get_var_env(char **, char *);

char		**lexer(char *line);
int		check_command(char **command);

char		*get_next_line(const int fd);
char		*get_next_line(const int );

void		check_auto_compet(t_shell *);
void		auto_completion(t_shell *);
void		completion(t_shell *);

void            loop_prompt(t_shell *);
char		*get_range_ascii(char *ascii, char input);

void		signal_handler(void);
void		check_signals(t_shell *);
void		exit_shell(t_shell *);

char		**lexer(char *line);
int		check_command(char **command);
int		globbing(char ***command);

void		strconcat(const char *, const char *, char *);

#endif /* !SHELL_H_ */
