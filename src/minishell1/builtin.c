/*
** builtin.c for builtin in /home/riamon_v/rendu/PSU/couver-shell/minishell1
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Wed May 18 15:23:24 2016 vincent riamon
** Last update Tue May 24 14:42:06 2016 vincent riamon
*/

#include "my.h"

int	my_env(__attribute__((unused))char **tab, t_shell *sh)
{
  aff_tab(sh->env);
  return (0);
}

static int	exit_setenv(char **tab, t_shell *sh)
{
  if (tab_len(tab) > 3)
    {
      fprintf(stderr, "setenv: Too many arguments.\n");
      return (0);
    }
  if (!tab[1])
    {
      aff_tab(sh->env);
      return (0);
    }
  return (1);
}

int		my_setenv(char **tab, t_shell *sh)
{
  int		i;
  int		bol;

  i = -1;
  bol = 0;
  if (!exit_setenv(tab, sh))
    return (-1);
  while (sh->env[++i])
    {
      if (!strncmp(sh->env[i], tab[1], strlen(tab[1])))
	{
	  free(sh->env[i]);
	  sh->env[i] = concat_str(tab[1], tab[2], '=');
	  bol = 1;
	}
    }
  if (!bol)
    {
      sh->env = realloc(sh->env, ((tab_len(sh->env) + 2) * sizeof(char *)));
      sh->env[i] = concat_str(tab[1], tab[2], '=');
      sh->env[i + 1] = NULL;
    }
  return (0);
}

int		my_unsetenv(char **tab, t_shell *sh)
{
  int		i;
  int		j;

  j = 0;
  if (!tab[1])
    {
      fprintf(stderr, "unsetenv: Too few arguments.\n");
      return (-1);
    }
  while (tab[++j])
    {
      i = -1;
      while (sh->env[++i] && strncmp(sh->env[i], tab[j], strlen(tab[j])));
      if (!sh->env[i])
	return (0);
      while (sh->env[i])
	{
	  sh->env[i] = sh->env[i + 1];
	  i = i + 1;
	}
      sh->env[i] = NULL;
    }
  return (0);
}
