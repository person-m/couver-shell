/*
** my.h for my.h in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Wed May 18 15:37:36 2016 Melvin Personnier
** Last update Tue May 24 11:27:40 2016 vincent riamon
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

char	**cpy_env(char **env);
char	*concat_str(char *s1, char *s2, char c);
void	strconcat(const char *s1, const char *s2, char *s3);
void	*my_malloc(int size);
void	free_tab(char **t);
int	tab_len(char **t);
int	my_getnbr(const char *str);
char	**my_str_to_wordtab_pattern(char *str, char *pattern);

void	aff_tab(char **t);
int	my_setenv(char **t, char ***env);
int	my_unsetenv(char **t, char ***env);
int	cmd_cd(char **t, char ***env);
int	my_echo(char **t, char ***env);
int	my_exit(char **t, char ***env);
int	my_env(char **t, char ***env);
int	minishell1(char **t, char ***env);
int	exec_sh1(char **t, char **env);

char	*get_var_env(char **env, char *name);
int	is_a_builtin(char *str);

#endif /* MY_H_ */
