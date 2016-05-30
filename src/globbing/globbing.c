/*
** globbing.c for globbing in /Users/couver_v/Epitech/rendu/couver-shell/src/globbing
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Sat May 28 16:10:09 2016 Vincent COUVERCHEL
** Last update Mon May 30 18:53:06 2016 vincent riamon
*/

#include <stdlib.h>
#include <stdio.h>
#include <glob.h>
#include "parser.h"
#include "shell.h"
#include "globbing_utils.c"

char		**insert_tab_in_tab(char **dest, char **src, int pos, int len)
{
  char		**new;

  if (!(new = malloc(sizeof(char *) * (tablen(dest) + tablen(src) - len + 1))))
    return (NULL);
  wordtabncpy(new, dest, pos);
  wordtabncpy(new + pos, src, tablen(src));
  wordtabncpy(new + pos + tablen(src),
	      dest + pos + len, tablen(dest + pos + len));
  free_tab(dest);
  return (new);
}

static int	glob_exec(char **command, int i)
{
  glob_t	globbuf;

  if (!is_exec(command, i)
      || glob(command[i], GLOB_TILDE, NULL, &globbuf))
    return (0);
  if (globbuf.gl_pathc)
  {
    free(command[i]);
    command[i] = strdup(globbuf.gl_pathv[0]);
  }
  globfree(&globbuf);
  return (0);
}

static int	glob_redirect(char **command, int i)
{
  glob_t	globbuf;

  if (!is_redirection_arg(command, i)
      || glob(command[i], GLOB_TILDE, NULL, &globbuf))
    return (0);
  if (globbuf.gl_pathc == 1)
  {
    free(command[i]);
    command[i] = strdup(globbuf.gl_pathv[0]);
  }
  else if (globbuf.gl_pathc > 1)
  {
    fprintf(stderr, "%s: Ambiguous.\n", command[i]);
    globfree(&globbuf);
    return (1);
  }
  globfree(&globbuf);
  return (0);
}

static int	glob_params(char ***command, int i)
{
  glob_t	globbuf;
  int		nb;

  if (is_redirection_arg(*command, i)
      || is_exec(*command, i)
      || glob((*command)[i], GLOB_TILDE, NULL, &globbuf))
    return (0);
  nb = globbuf.gl_pathc;
  if (globbuf.gl_pathc)
    *command = insert_tab_in_tab(*command, globbuf.gl_pathv, i, 1);
  globfree(&globbuf);
  return ((nb - 1) * !!nb);
}

int		globbing(char ***command)
{
  int		i;

  i = 0;
  while ((*command)[i])
  {
    if (!is_end_of_command((*command)[i]) && !is_quote((*command)[i])
	&& !is_redirection((*command)[i]))
    {
      glob_exec(*command, i);
      glob_redirect(*command, i);
      i += glob_params(command, i);
    }
    i = get_next_match_arg(*command, i);
  }
  return (0);
}
