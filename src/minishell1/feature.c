/*
** logo.c for logo.c in /home/riamon_v/rendu/PSU/couver-shell/src/minishell1
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Thu Jun  2 19:22:06 2016 vincent riamon
** Last update Sun Jun  5 21:17:05 2016 Melvin Personnier
*/

#include "shell.h"

int		logo(__attribute__((unused))char **cmd, t_shell *sh)
{
  char		**tab;

  tab = my_malloc(sizeof(char *) * 3);
  tab[0] = "cat";
  tab[1] = "./.logo.txt";
  tab[2] = NULL;
  if (fork() == 0)
    {
      if (execve("/bin/cat", tab, sh->env) == -1)
	return (-1);
    }
  else
    wait(NULL);
  free(tab);
  return (0);
}

int		made_by(__attribute__((unused))char **cmd, t_shell *sh)
{
  char		**tab;

  tab = my_malloc(sizeof(char *) * 3);
  tab[0] = "cat";
  tab[1] = "./.madeby.txt";
  tab[2] = NULL;
  if (fork() == 0)
    {
      if (execve("/bin/cat", tab, sh->env) == -1)
	return (-1);
    }
  else
    wait(NULL);
  free(tab);
  return (0);
}

int		man_couver(char **cmd, t_shell *sh)
{
  char		**tab;

  if (cmd[0] && !strcmp(cmd[0], "\"man\"") &&
      cmd[1] && !strcmp(cmd[1], "\"couver-shell\""))
    {
      tab = my_malloc(sizeof(char *) * 3);
      tab[0] = "less";
      tab[1] = "./.man_couver";
      tab[2] = NULL;
      if (fork() == 0)
	{
	  if (execve("/usr/bin/less", tab, sh->env) == -1)
	    return (-1);
	}
      else
	wait(NULL);
      free(tab);
      sh->ret = 0;
      return (1);
    }
  return (0);
}
