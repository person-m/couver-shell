/*
** couvrc.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/couvrc/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Wed May 25 18:30:25 2016 Melvin Personnier
** Last update Sun Jun  5 22:00:27 2016 Melvin Personnier
*/

#include <stdio.h>
#include "couvrc.h"

void	strconcat(char*, char*, char*);

static void	add_str(char **s, int fd, char **cmd)
{
  while ((*s = get_next_line(fd)))
    {
      *cmd = my_realloc(*cmd, sizeof(char) * (strlen(*s) + strlen(*cmd) + 2));
      strconcat(*cmd, *s, *cmd);
      (*cmd)[strlen(*cmd) + 1] = 0;
      (*cmd)[strlen(*cmd)] = ';';
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
