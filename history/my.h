/*
** get_next_line.h for get_next_line in /home/riamon_v/rendu/CPE/CPE_2015_getnextline
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Mon Jan  4 13:27:16 2016 vincent riamon
** Last update Sun May 22 15:20:45 2016 vincent riamon
*/

#ifndef MY_H
# define MY_H

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#ifndef READ_SIZE
# define READ_SIZE (7)
#endif /* !READ_SIZE */

int	tab_len(char **tab);
char	*get_next_line(const int fd);
void	*my_malloc(int size);
void	free_tab(char **tab);
char	*get_var_env(char **env, char *name);
char	*concat_str(char *str, char *s2, char c);

#endif /* !MY_H */
