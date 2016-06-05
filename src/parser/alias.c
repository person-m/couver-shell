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

static int	replace_alias(char ***cmd, t_shell *sh)
{
  char	**new_cmd;
  char	*old;

  if (!**cmd)
    return (1);
  if (strlen((*cmd)[0]) > 1)
  {
    (*cmd)[0]++;
    (*cmd)[0][strlen((*cmd)[0]) - 1] = 0;
  }
  old = (*cmd)[0];
  if (is_alias(*cmd, sh))
  {
    new_cmd = lexer(**cmd, 0);
    *cmd = insert_tab_in_tab(*cmd, new_cmd, 0, 1);
    if (!strncmp(old, *new_cmd + 1, strlen(*new_cmd + 1) - 1))
    {
      free(new_cmd);
      return (1);
    }
    free(new_cmd);
    return (0);
  }
  return (1);
}

char	**alias(char **cmd, t_shell *sh)
{
  int	i;

  i = 0;
  while (!replace_alias(&cmd, sh) && i < 128)
    i++;
  if (i == 128)
  {
    fprintf(stderr, "Alias loop.\n");
    return (NULL);
  }
  return (cmd);
}

