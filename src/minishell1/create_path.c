/*
** create_path.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Sat Jun  4 21:24:16 2016 Melvin Personnier
** Last update Sat Jun  4 21:24:36 2016 Melvin Personnier
*/

#include "my.h"

char		*create_path()
{
  char		*pathbuf;
  size_t	n;

  n = confstr(_CS_PATH, NULL, (size_t) 0);
  pathbuf = my_malloc(sizeof(char) * n);
  confstr(_CS_PATH, pathbuf, n);
  return (pathbuf);
}
