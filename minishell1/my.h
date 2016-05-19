/*
** my.h for my.h in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Wed May 18 15:37:36 2016 Melvin Personnier
** Last update Thu May 19 15:58:44 2016 vincent riamon
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
char	*get_var_env(char **env, char *name);
void	my_pwd(char **env, char *name);
void	aff_tab(char **tab);
void	*my_malloc(int size);
int	tab_len(char **tab);
void	my_setenv(char **tab, char ***env);
void	my_unsetenv(char **tab, char ***env);
char	*get_var_env(char **env, char *name);
void	cmd_cd(char **tab, char **tmp);
void	verif_cd(char **tab, char **env);
void	my_echo(char **tab, char **env);

#endif /* MY_H_ */
