/*
** shell.h for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:50:52 2016
** Last update Sun Jun  5 03:43:29 2016 vincent riamon
*/

#ifndef SHELL_H_
# define SHELL_H_

/*
**	Libraries
*/

# define _GNU_SOURCE

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "prompt.h"

typedef struct	s_shell
{
  char		**env;
  char		**alias;
  char		**history;
  char		**set;
  int		size_hist;
  int		ret;
  int		bol;
  t_prompt	*prompt;
}		t_shell;

char		**alias(char **tab, t_shell *sh);

void		get_std_input(t_shell *sh);

char		**cpy_env(char **env);
char		*nbr_in_str(int nb);
char		**my_str_to_wordtab_pattern(char *s, char *pattern);
int		minishell1(char **tab, t_shell *sh);
int		lenstr(char *str, char c);
int		is_a_builtin(char *str);
int		tab_len(char **tab);
void		aff_tab(char **tab);
void		free_tab(char **tab);
void		create_alias(t_shell *sh);
void		create_oldpwd(t_shell *sh);
void		create_set(t_shell *sh);
void		*my_malloc(int size);
char		*couvrc(char **env);
int		logo(char **cmd, t_shell *sh);
int		man_couver(char **cmd, t_shell *sh);
int		made_by(char **cmd, t_shell *sh);
void		the_execution(char **cmd, t_shell *sh);

void		set_var_env(char ***env, char *var, char *value);
void		is_to_large_history(t_shell *sh);
void		fill_history(t_shell *sh);
void		update_history(char *line, t_shell *sh);
char		*wordtab_in_str(char **tab, int mode);
int		create_history_file(char **hist, t_shell *sh);
char		**error_history(char *var);
char		*error_history2();

int		replace_exclam_dot(char ***cmd, t_shell *sh);
char		*get_var(char *str);
char		**insert_tab_in_tab(char **dest, char **src,
				     int pos, int len);
char		**insert_str_in_tab(char **dest, char *src, int pos, int len);
char		*get_var_env(char **, char *);

char		*get_next_line(const int fd);
char		*get_next_line(const int);

void		check_auto_compet(t_shell *);
void		auto_completion(t_shell *);
void		completion(t_shell *);
char		is_subcommand_in_path(t_prompt *, DIR *, char);
int		rebind(char **cmd, t_shell *sh);

void            loop_prompt(t_shell *);
char		get_input(t_shell *);
void		which_input(t_shell *, char);
char		*get_range_ascii(char *ascii, char input);
void		more_complex_string(t_shell *, char *);
void		move_left_word(t_shell *);
void		move_right_word(t_shell *);

void		signal_handler(void);
void		check_signals(t_shell *);
void		exit_shell(t_shell *);

void		do_the_thing(t_shell *sh, char ***cmd, int flag);
char		**lexer(char *line, int flag);
int		check_command(char **command);
int		globbing(char ***command);
void		backquote(char ***command, t_shell *sh);
void		del_quote(char **command);
char		**glob_command(char **command);
int		is_glob_redirect(char **str);
int		replace_variables(char ***cmd, t_shell *sh);

int		repeat(char **, t_shell *);

void		strconcat(const char *, const char *, char *);
char		*concat_str(char *, char *, char);
int		my_getnbr(const char *str);

#endif /* !SHELL_H_ */
