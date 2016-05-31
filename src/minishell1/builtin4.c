/*
** builtin4.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Mon May 30 22:36:13 2016 Melvin Personnier
** Last update Tue May 31 16:12:07 2016 vincent riamon
*/

#include "my.h"

int		is_alphanum(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if ((str[i] >= '0' && str[i] <= '9')
	  || (str[i] >= 'a' && str[i] <= 'z')
	  || (str[i] >= 'A' && str[i] <= 'Z'))
	i = i + 1;
      else
	return (0);
    }
  return (1);
}

static void	print_set(char **tab)
{
  int		i;

  i = -1;
  printf("_\t");
  while (tab[++i])
    {
      printf("%s", tab[i]);
      if (tab[i + 1] != NULL)
	printf(" ");
    }
  printf("\n\n");
}

int		cmd_set(char **tab, t_shell *sh)
{
  sh->alias = sh->alias;
  print_set(tab);
  return (0);
}
