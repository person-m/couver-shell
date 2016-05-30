/*
** ptn_fct.c for ptn_fct.c in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Fri May 20 15:21:34 2016 Melvin Personnier
** Last update Mon May 30 22:42:33 2016 Melvin Personnier
*/

#include "my.h"

static void	init_builtins_cmp(char **builtins_cmp)
{
  builtins_cmp[0] = "cd";
  builtins_cmp[1] = "echo";
  builtins_cmp[2] = "exit";
  builtins_cmp[3] = "setenv";
  builtins_cmp[4] = "unsetenv";
  builtins_cmp[5] = "alias";
  builtins_cmp[6] = "history";
  builtins_cmp[7] = "set";
  builtins_cmp[8] = "bind";
}

static void	init_builtins(int (**builtins)(char **tab, t_shell *sh))
{
  builtins[0] = &cmd_cd;
  builtins[1] = &my_echo;
  builtins[2] = &my_exit;
  builtins[3] = &my_setenv;
  builtins[4] = &my_unsetenv;
  builtins[5] = &my_alias;
  builtins[6] = &cmd_history;
  builtins[7] = &cmd_set;
  builtins[8] = &rebind;
}

static int     builtins(char **tab, t_shell *sh)
{
  int	(*builtins[9])(char **tab, t_shell *sh);
  char	*builtins_cmp[9];
  int	i;
  int	is_builtin;

  i = -1;
  is_builtin = 1;
  init_builtins_cmp(builtins_cmp);
  init_builtins(builtins);
  while (++i < 9)
    {
      if ((strcmp(tab[0], builtins_cmp[i])) == 0)
	is_builtin = builtins[i](tab, sh);
    }
  return (is_builtin);
}

int	minishell1(char **tab, t_shell *sh)
{
  int	is_builtin;

  if ((is_builtin = builtins(tab, sh)) == 1)
    return (exec_sh1(tab, sh->env));
  return (is_builtin);
}
