/*
** main.c for 42sh in /home/hedia_m/couver-shell/minishell2
** 
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
** 
** Started on  Mon May 23 13:02:51 2016 mohamed-laid hedia
** Last update Mon May 23 13:25:06 2016 mohamed-laid hedia
*/

#include "mo.h"

int	my_tablen(char **tab)
{
  int	i;

  i = 0;
  while (tab[i])
    {
      i = i + 1;
    }
  return (i);
}

int	main(int ac, char **argv, char **tab)
{
  int	i;
  char	**env;

  i = 0;
  env = malloc(sizeof(char *) * (my_tablen(tab) + 1));
  while (tab[i])
    {
      env[i] = malloc(sizeof(char) * (strlen(tab[i]) + 1));
      env[i] = strcpy(env[i], tab[i]);
      i = i + 1;
      env[i] = 0;
    }
  the_execution(argv + 1, env);
  return (0);
}
