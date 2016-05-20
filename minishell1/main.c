/*
** main.c for main in /home/riamon_v/rendu/PSU/couver-shell/minishell1
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Wed May 18 15:18:36 2016 vincent riamon
** Last update Fri May 20 17:52:55 2016 vincent riamon
*/

#include "my.h"

int		main(int argc, char **argv, char **env)
{
  char		**tab;
  char		**tmp;

  tab = malloc(sizeof(char *) * 6);
  tab[0] = "setenv";
  tab[1] = "a";
  tab[2] = NULL;
  tab[3] = NULL;
  tab[4] = "d";
  tab[5] = NULL;
  tmp = cpy_env(env);
  built_in(tab, &tmp);
  if (!strcmp(tab[0], "setenv") ||
      !strcmp(tab[0], "unsetenv"))
    aff_tab(tmp);
  /* free_tab(tmp); */
  return (0);
}
