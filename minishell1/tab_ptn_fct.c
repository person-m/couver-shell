/*
** ptn_fct.c for ptn_fct.c in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Fri May 20 15:21:34 2016 Melvin Personnier
** Last update Fri May 20 19:52:33 2016 Melvin Personnier
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

static void	init_builtins(void (**builtins)(char **tab, char ***env))
{
  builtins[0] = &cmd_cd;
  builtins[1] = &my_echo;
  builtins[2] = &my_exit;
  builtins[3] = &my_setenv;
  builtins[4] = &my_unsetenv;
  builtins[5] = &my_env;
}

int	tab_ptn_fct(char **tab, char ***env)
{
  void	(*builtins[6])(char **tab, char ***env);
  char	*builtins_cmp[6];
  int	i;
  int	is_builtin;

  i = -1;
  is_builtin = 0;
  init_builtins_cmp(builtins_cmp);
  init_builtins(builtins);
  while (++i < 6)
    {
      if ((strcmp(tab[0], builtins_cmp[i])) == 0)
	{
	  builtins[i](tab, env);
	  is_builtin = 1;
	}
    }
  return (is_builtin);
}
