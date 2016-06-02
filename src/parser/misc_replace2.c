/*
** misc_replace2.c for misc_replace2 in /home/riamon_v/rendu/PSU/couver-shell/src/parser
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Fri Jun  3 00:10:34 2016 vincent riamon
** Last update Fri Jun  3 00:33:56 2016 vincent riamon
*/

#include "shell.h"

int		there_is_accolade(char *str, int *inc)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] == '{')
	{
	  *inc += 1;
	  return (1);
	}
      i = i + 1;
    }
  return (0);
}
