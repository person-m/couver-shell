/*
** utils.c for utils.c in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Wed May 18 15:46:12 2016 Melvin Personnier
** Last update Wed May 18 15:54:34 2016 Melvin Personnier
*/

#include "my.h"

void	*my_malloc(int size)
{
  void	*ptr;

  ptr = malloc(size);
  if (ptr == NULL)
    {
      fprintf(stderr, "malloc failure!\n");
      exit(1);
    }
  return (ptr);
}
