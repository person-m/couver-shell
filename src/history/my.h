/*
** get_next_line.h for get_next_line in /home/riamon_v/rendu/CPE/CPE_2015_getnextline
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Mon Jan  4 13:27:16 2016 vincent riamon
** Last update Wed May 25 16:26:28 2016 vincent riamon
*/

#ifndef MY_H
# define MY_H

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "../minishell1/my.h"

#ifndef READ_SIZE
# define READ_SIZE (7)
#endif /* !READ_SIZE */

int	tab_len(char **tab);
char	*get_next_line(const int fd);
void	*my_malloc(int size);
void	free_tab(char **tab);
char	*get_var_env(char **env, char *name);
char	*concat_str(char *str, char *s2, char c);

/* char	**fill_history(char **env); */
/* void	update_history(char **line, char ***tab, char **env); */
/* int		cmd_history(char **tab, t_shell *sh); */

#endif /* !MY_H */
