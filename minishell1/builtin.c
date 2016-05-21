/*
** builtin.c for builtin in /home/riamon_v/rendu/PSU/couver-shell/minishell1
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Wed May 18 15:23:24 2016 vincent riamon
** Last update Sat May 21 13:23:44 2016 vincent riamon
*/

#include "my.h"

int	my_env(__attribute((unused))char **tab, char ***env)
{
  aff_tab(*env);
  return (0);
}

int		exit_setenv(char **tab, char ***env)
{
  if (tab_len(tab) > 3)
    {
      fprintf(stderr, "setenv: Too many arguments.\n");
      return (0);
    }
  if (!tab[1])
    {
      aff_tab(*env);
      return (0);
    }
  return (1);
}

int		my_setenv(char **tab, char ***env)
{
  int		i;
  int		bool;

  i = -1;
  bool = 0;
  if (!exit_setenv(tab, env))
    return (-1);
  while ((*env)[++i])
    {
      if (!strncmp((*env)[i], tab[1], strlen(tab[1])))
	{
	  (*env)[i] = concat_str(tab[1], tab[2], '=');
	  bool = 1;
	}
    }
  if (!bool)
    {
      *env = realloc(*env, ((tab_len(*env) + 2) * sizeof(char *)));
      (*env)[i] = concat_str(tab[1], tab[2], '=');
      (*env)[i + 1] = NULL;
    }
  return (0);
}

int		my_unsetenv(char **tab, char ***env)
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
      while ((*env)[++i] && strncmp((*env)[i], tab[j], strlen(tab[j])));
      if (!(*env)[i])
	return (0);
      while ((*env)[i])
	{
	  (*env)[i] = (*env)[i + 1];
	  i = i + 1;
	}
      (*env)[i] = NULL;
    }
  return (0);
}

int		cmd_cd(char **tab, char ***env)
{
  char		*s;

  if (!(s = get_var_env(*env, "OLDPWD=")));
  else
    my_pwd(*env, "OLDPWD=");
  if (tab_len(tab) > 2)
    {
      fprintf(stderr, "cd: Too many arguments.\n");
      return (-1);
    }
  if (!tab[1])
    chdir(get_var_env(*env, "HOME="));
  else if (!strcmp(tab[1], "-"))
    chdir(s);
  else if (chdir(tab[1]) == -1)
    {
      verif_cd(tab);
      return (-1);
    }
  my_pwd(*env, "PWD=");
  return (0);
}
