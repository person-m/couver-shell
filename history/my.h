/*
** get_next_line.h for get_next_line in /home/riamon_v/rendu/CPE/CPE_2015_getnextline
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Mon Jan  4 13:27:16 2016 vincent riamon
** Last update Sun May 22 13:33:32 2016 vincent riamon
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

#endif /* !MY_H */
