/*
** order_by_asc.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Sat Jun  4 16:17:25 2016 Melvin Personnier
** Last update Sat Jun  4 16:20:56 2016 Melvin Personnier
*/

#include "my.h"

char		**my_sort(char **tabl)
{
  int		t;
  int		i;
  char		*s;

  t = 1;
  while (t)
    {
      t = 0;
      i = 0;
      while (tabl[i + 1] != 0)
	{
	  if (strcmp(tabl[i], tabl[i + 1]) > 0)
	    {
	      t = 1;
	      s = tabl[i];
	      tabl[i] = tabl[i + 1];
	      tabl[i + 1] = s;
	    }
	  i = i + 1;
	}
    }
  return (tabl);
}
