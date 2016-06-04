/*
** ptn_fct.c for ptn_fct.c in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Fri May 20 15:21:34 2016 Melvin Personnier
** Last update Sat Jun  4 16:02:19 2016 Melvin Personnier
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
  builtins_cmp[8] = "unset";
  builtins_cmp[9] = "bind";
  builtins_cmp[10] = "couver";
  builtins_cmp[11] = "madeby";
  builtins_cmp[12] = "if";
  builtins_cmp[13] = "repeat";
  builtins_cmp[14] = "which";
  builtins_cmp[15] = "where";
  builtins_cmp[16] = "unalias";
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
  builtins[8] = &my_unset;
  builtins[9] = &rebind;
  builtins[10] = &logo;
  builtins[11] = &made_by;
  builtins[12] = &my_if;
  builtins[13] = &repeat;
  builtins[14] = &my_which;
  builtins[15] = &my_where;
  builtins[16] = &my_unalias;
}

static int     builtins(char **tab, t_shell *sh)
{
  int	(*builtins[17])(char **tab, t_shell *sh);
  char	*builtins_cmp[17];
  int	i;
  int	is_builtin;

  i = -1;
  is_builtin = 1;
  init_builtins_cmp(builtins_cmp);
  init_builtins(builtins);
  while (++i < 17)
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
    return (exec_sh1(tab, sh));
  return (is_builtin);
}
