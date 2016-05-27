/*
** couvrc.h for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/couvrc/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Wed May 25 18:30:04 2016 Melvin Personnier
** Last update Thu May 26 23:49:20 2016 Melvin Personnier
*/

#ifndef MY_H
# define MY_H

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#ifndef READ_SIZE
# define READ_SIZE (42)
#endif /* !READ_SIZE */

char	*get_next_line(const int fd);
void	*my_malloc(int size);
void	free_tab(char **tab);
char	*get_var_env(char **env, char *name);
char	*concat_str(char *str, char *s2, char c);

#endif /* MY_H_ */
