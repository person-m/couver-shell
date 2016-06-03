/*
** verifs.c for 42sh in /home/hedia_m/couver-shell/minishell2
**
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
**
** Started on  Fri May 20 21:39:14 2016 mohamed-laid hedia
** Last update Fri Jun  3 01:08:09 2016 Melvin Personnier
*/

#include "mo.h"

int	next_is_pipe(char **tab, int i)
{
  while (tab[i] != 0)
    {
      if (!strcmp(tab[i], "|"))
	return (1);
      else if (!strcmp(tab[i], "||") || !strcmp(tab[i], "&&") ||
	       !strcmp(tab[i], ";"))
	return (0);
      else
	i = i + 1;
    }
  return (0);
}

int	is_sep_param(char *str)
{
  if (strcmp(str, "||") && strcmp(str, "&&") && strcmp(str, "|") &&
      strcmp(str, ";") && strcmp(str, "&"))
    return (0);
  return (1);
}

int	is_builtin(char *str)
{
  if (strcmp(str, "cd") && strcmp(str, "echo") && strcmp(str, "exit") &&
      strcmp(str, "setenv") && strcmp(str, "unsetenv")
      && strcmp(str, "alias") && strcmp(str, "history") &&
      strcmp(str, "set") && strcmp(str, "unset") && strcmp(str, "bind")
      && strcmp(str, "couver") && strcmp(str, "madeby")&&
      strcmp(str, "if"))
    return (0);
  return (1);
}
