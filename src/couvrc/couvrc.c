/*
** couvrc.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/couvrc/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Wed May 25 18:30:25 2016 Melvin Personnier
** Last update Fri May 27 00:34:40 2016 Melvin Personnier
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

char	*couvrc(char **env)
{
  char	*home;
  int	fd;
  char	*s;
  char	*cmd;

  cmd = my_malloc(sizeof(char) * 1);
  cmd[0] = 0;
  home = concat_str(get_var_env(env, "HOME="), ".couvrc", '/');
  if (home == NULL)
    {
      if ((fd = open(".couvrc", O_RDONLY)) == -1)
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

/*
int	main(int argc, char **argv, char **env)
{
  char	*s;

  if ((s = couvrc(env)))
    printf("%s\n", s);
  free(s);
}
*/
