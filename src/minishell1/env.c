/*
** builtin.c for builtin in /home/riamon_v/rendu/PSU/couver-shell/minishell1
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Wed May 18 15:23:24 2016 vincent riamon
** Last update Sun Jun  5 03:28:13 2016 Melvin Personnier
*/

#include "my.h"

int		my_env(t_shell *sh)
{
  aff_tab(sh->env);
  return (0);
}

static int	exit_setenv(char **tab)
{
  if (tab_len(tab) > 3)
    {
      fprintf(stderr, "setenv: Too many arguments.\n");
      return (0);
    }
  if ((tab[1] && !is_alphanum(tab[1])))
    {
      fprintf(stderr, "setenv: Variable name must"
	      " contain alphanumeric characters.\n");
      return (0);
    }
  return (1);
}

int		my_setenv(char **tab, t_shell *sh)
{
  int		i;

  i = -1;
  sh->bol = 0;
  if (!exit_setenv(tab))
    return (-1);
  if (!tab[1])
    return (my_env(sh));
  while (sh->env[++i])
    {
      if (!strncmp(sh->env[i], tab[1], strlen(tab[1]))
	  && sh->env[i][strlen(tab[1])] == '=')
	{
	  free(sh->env[i]);
	  sh->env[i] = concat_str(tab[1], tab[2], '=');
	  sh->bol = 1;
	}
    }
  if (!sh->bol)
    {
      sh->env = realloc(sh->env, ((tab_len(sh->env) + 2) * sizeof(char *)));
      sh->env[i] = concat_str(tab[1], tab[2], '=');
      sh->env[i + 1] = NULL;
    }
  return (0);
}

int		is_already_in_env(char **my_env, char *str)
{
  int		i;
  char		*str2;

  i = 0;
  str2 = my_malloc(sizeof(char) * (strlen(str) + 2));
  str2 = strcpy(str2, str);
  str2[strlen(str)] = '=';
  str2[strlen(str) + 1] = 0;
  while (my_env[i])
    {
      if (!(strncmp(my_env[i], str2, strlen(str2))))
	{
	  free(str2);
	  return (i);
	}
      i++;
    }
  free(str2);
  return (i);
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
      i = is_already_in_env(sh->env, tab[j]);
      while (sh->env[i] && sh->env[i + 1])
	{
	  sh->env[i] = sh->env[i + 1];
	  i = i + 1;
	}
      sh->env[i] = NULL;
    }
  return (0);
}
