/*
** ptn_fct.c for ptn_fct.c in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Fri May 20 15:21:34 2016 Melvin Personnier
** Last update Sat May 21 14:59:06 2016 Melvin Personnier
*/

#include "my.h"

static void	init_builtins_cmp(char **builtins_cmp)
{
  builtins_cmp[0] = "cd";
  builtins_cmp[1] = "echo";
  builtins_cmp[2] = "exit";
  builtins_cmp[3] = "setenv";
  builtins_cmp[4] = "unsetenv";
  builtins_cmp[5] = "env";
}

static void	init_builtins(int (**builtins)(char **tab, char ***env))
{
  builtins[0] = &cmd_cd;
  builtins[1] = &my_echo;
  builtins[2] = &my_exit;
  builtins[3] = &my_setenv;
  builtins[4] = &my_unsetenv;
  builtins[5] = &my_env;
}

int     builtins(char **tab, char ***env)
{
  int	(*builtins[6])(char **tab, char ***env);
  char	*builtins_cmp[6];
  int	i;
  int	is_builtin;

  i = -1;
  is_builtin = 1;
  init_builtins_cmp(builtins_cmp);
  init_builtins(builtins);
  while (++i < 6)
    {
      if ((strcmp(tab[0], builtins_cmp[i])) == 0)
	is_builtin = builtins[i](tab, env);
    }
  return (is_builtin);
}

int	minishell1(char **tab, char ***env)
{
  int	is_builtin;

  if ((is_builtin = builtins(tab, env)) == 1)
    return (execve(tab[0], tab, *env));
  return (is_builtin);
}
