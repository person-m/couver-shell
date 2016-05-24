/*
** my.h for my.h in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Wed May 18 15:37:36 2016 Melvin Personnier
** Last update Tue May 24 14:43:11 2016 vincent riamon
*/

#ifndef	MY_H_
# define MY_H_

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include "../../include/shell.h"

char	**cpy_env(char **env);
char	*concat_str(char *s1, char *s2, char c);
void	strconcat(const char *s1, const char *s2, char *s3);
void	*my_malloc(int size);
void	free_tab(char **t);
int	tab_len(char **t);
int	my_getnbr(const char *str);
char	**my_str_to_wordtab_pattern(char *str, char *pattern);

void	aff_tab(char **t);
int	my_setenv(char **t, t_shell *sh);
int	my_unsetenv(char **t, t_shell *sh);
int	cmd_cd(char **t, t_shell *sh);
int	my_echo(char **t, t_shell *sh);
int	my_exit(char **t, t_shell *sh);
int	my_env(char **t, t_shell *sh);
int	minishell1(char **t, t_shell *sh);
int	exec_sh1(char **t, char **env);

char	*get_var_env(char **env, char *name);
int	is_a_builtin(char *str);

#endif /* MY_H_ */
