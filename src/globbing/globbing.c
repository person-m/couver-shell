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
  if (src)
    wordtabncpy(new + pos, src, tablen(src));
  wordtabncpy(new + pos + tablen(src),
	      dest + pos + len, tablen(dest + pos + len));
  return (new);
}

int	is_glob_redirect(char **str)
{
  glob_t	globbuf;
  int		ret;

  ret = glob(*str, GLOB_TILDE | GLOB_NOMAGIC, NULL, &globbuf);
  if (ret == GLOB_NOMATCH)
  {
    fprintf(stderr, "%s: No match.\n", *str);
    return (0);
  }
  else if (ret)
    return (0);
  if (globbuf.gl_pathc == 1)
  {
    *str = strdup(globbuf.gl_pathv[0]);
  }
  else if (globbuf.gl_pathc > 1)
  {
    fprintf(stderr, "%s: Ambiguous.\n", *str);
    globfree(&globbuf);
    return (0);
  }
  globfree(&globbuf);
  return (1);
}

char		**glob_parameters(char **command, int *i)
{
  glob_t	globbuf;
  int		nb;
  int		ret;

  ret = glob(command[*i], GLOB_TILDE | GLOB_NOMAGIC, NULL, &globbuf);
  if (ret == GLOB_NOMATCH)
  {
    fprintf(stderr, "%s: No match.\n", *command);
    return (NULL);
  }
  nb = globbuf.gl_pathc;
  if (globbuf.gl_pathc)
    command = insert_tab_in_tab(command, globbuf.gl_pathv, *i, 1);
  globfree(&globbuf);
  *i += (nb - 1) * !!nb;
  return (command);
}

int	glob_executable(char **str)
{
  glob_t	globbuf;
  int		ret;

  ret = glob(*str, GLOB_TILDE | GLOB_NOMAGIC, NULL, &globbuf);
  if (ret == GLOB_NOMATCH)
  {
    fprintf(stderr, "%s: No match.\n", *str);
    return (0);
  }
  else if (ret)
    return (0);
  if (globbuf.gl_pathc)
  {
    *str = strdup(globbuf.gl_pathv[0]);
  }
  globfree(&globbuf);
  return (1);
}

char	**glob_command(char **command)
{
  int	i;
  int	quote;

  quote = 0;
  i = 1;
  if (!glob_executable(command))
    return (NULL);
  quote = (strcmp(command[0], "\"")) ? quote : !quote;
  quote = (strcmp(command[0], "'")) ? quote : !quote;
  while (command[i])
  {
    quote = (strcmp(command[i], "\"")) ? quote : !quote;
    quote = (strcmp(command[i], "'")) ? quote : !quote;
    if (strcmp(command[i], "\"") && strcmp(command[i], "'") && !quote)
    {
      if (!(command = glob_parameters(command, &i)))
	return (NULL);
    }
    i++;
  }
  del_quote(command);
  return (command);
}
