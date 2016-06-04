/*
** unalias.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Sat Jun  4 15:58:07 2016 Melvin Personnier
** Last update Sat Jun  4 15:58:26 2016 Melvin Personnier
*/

#include "my.h"

static int	is_already_in_alias(char **my_alias, char *str)
{
  int    	i;
  char		*str2;

  i = 0;
  str2 = my_malloc(sizeof(char) * (strlen(str) + 2));
  str2 = strcpy(str2, str);
  str2[strlen(str)] = '=';
  str2[strlen(str) + 1] = 0;
  while (my_alias[i])
    {
      if (!(strncmp(my_alias[i], str2, strlen(str2))))
	{
	  free(str2);
	  return (i);
	}
      i++;
    }
  free(str2);
  return (i);
}

int		my_unalias(char **tab, t_shell *sh)
{
  int		i;
  int		j;

  j = 0;
  if (!tab[1])
    {
      fprintf(stderr, "unalias: Too few arguments.\n");
      return (-1);
    }
  while (tab[++j])
    {
      i = is_already_in_alias(sh->alias, tab[j]);
      while (sh->alias[i] && sh->alias[i + 1])
	{
	  sh->alias[i] = sh->alias[i + 1];
	  i = i + 1;
	}
      sh->alias[i] = NULL;
    }
  return (0);
}
