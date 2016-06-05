/*
** couvrc.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/couvrc/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Wed May 25 18:30:25 2016 Melvin Personnier
** Last update Sun Jun  5 03:41:25 2016 vincent riamon
*/

#include <stdio.h>
#include "couvrc.h"

static void	add_str(char **s, int fd, char **cmd)
{
  while ((*s = get_next_line(fd)))
    {
      *cmd = realloc(*cmd, sizeof(char) * (strlen(*s) + strlen(*cmd) + 4));
      *cmd = strcat(*cmd, *s);
      (*cmd)[strlen(*cmd) + 1] = 0;
      (*cmd)[strlen(*cmd)] = ';';
      free(*s);
    }
}

char		*couvrc(char **env)
{
  char		*home;
  int		fd;
  char		*s;
  char		*cmd;

  cmd = my_malloc(sizeof(char) * 1);
  cmd[0] = 0;
  home = concat_str(get_var_env(env, "HOME="), ".couverc", '/');
  if (home == NULL)
    {
      if ((fd = open(".couverc", O_RDONLY)) == -1)
	return (NULL);
      add_str(&s, fd, &cmd);
      return (cmd);
    }
  if ((fd = open(home, O_RDONLY)) == -1)
    return (NULL);
  add_str(&s, fd, &cmd);
  free(home);
  return (cmd);
}
