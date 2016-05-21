/*
** my.h for my.h in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Wed May 18 15:37:36 2016 Melvin Personnier
** Last update Sat May 21 18:01:54 2016 vincent riamon
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
void	my_pwd(char **env, char *name);
void	*my_malloc(int size);
void	free_tab(char **tab);
int	tab_len(char **tab);
int	my_getnbr(const char *str);
char	**my_str_to_wordtab_pattern(char *str, char *pattern);

void	aff_tab(char **tab);
int	my_setenv(char **tab, char ***env);
int	my_unsetenv(char **tab, char ***env);
int	cmd_cd(char **tab, char ***env);
void	verif_cd(char **tab);
int	my_echo(char **tab, char ***env);
int	my_exit(char **tab, char ***env);
int	my_env(char **tab, char ***env);
int	minishell1(char **tab, char ***env);
int	exec_sh1(char **tab, char **env);

char	*get_var_env(char **env, char *name);

#endif /* MY_H_ */
