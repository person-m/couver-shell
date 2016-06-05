/*
** alias.c for alias in /Users/couver_v/Epitech/rendu/couver-shell/src/parser
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Thu Jun  2 21:54:33 2016 Vincent COUVERCHEL
** Last update Thu Jun  2 21:54:33 2016 Vincent COUVERCHEL
*/

#include "my.h"

char	**alias(char **cmd, t_shell *sh)
{
  char	**new_cmd;

  if (!*cmd)
    return (cmd);
  if (strlen(cmd[0]) > 1)
  {
    cmd[0]++;
    cmd[0][strlen(cmd[0]) - 1] = 0;
  }
  if (is_alias(cmd, sh))
  {
    new_cmd = lexer(*cmd, 0);
    cmd = insert_tab_in_tab(cmd, new_cmd, 0, 1);
  }
  return (cmd);
}
