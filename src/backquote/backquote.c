/*
** backquote.c for backquote in /Users/couver_v/Epitech/rendu/couver-shell/src/backquote
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Fri May 27 16:42:28 2016 Vincent COUVERCHEL
** Last update Fri May 27 16:42:28 2016 Vincent COUVERCHEL
*/

#define BUF_SIZE 1024

#include "shell.h"
#include "backquote_utils.c"
#include "backquote_misc.c"

static char	**insert_str_in_tab(char **dest, char *src, int pos, int len)
{
  char		**new;

  if (!(new = malloc(sizeof(char *) * (tab_len(dest) - len + 2))))
    return (NULL);
  wordtabncpy(new, dest, pos);
  new[pos] = src;
  wordtabncpy(new + pos + 1,
	      dest + pos + len, tab_len(dest + pos + len));
  free_tab(dest);
  return (new);
}

static void	tronc_tab(char **dest, int pos, int len)
{
  if (!dest || tab_len(dest) < pos + len)
    return ;
  while (dest[pos + len])
  {
    dest[pos] = dest[pos + len];
    pos++;
  }
  dest[pos] = NULL;
}

static void	init_backquote(int q[2], char ***new_command, int *i)
{
  q[0] = 0;
  q[1] = 0;
  *new_command = NULL;
  *i = -1;
}

static void	free_backquote(char **new_command, char **sub_command)
{
  free_tab(new_command);
  free_tab(sub_command);
}

void	backquote(char ***command, t_shell *sh)
{
  int	i;
  int	j;
  char	**new_command;
  char	**sub_command;
  char	*new_line;
  int	q[2];

  init_backquote(q, &new_command, &i);
  while ((*command)[++i])
  {
    q[0] = strcmp((*command)[i], "\"") ? q[0] : !q[0];
    q[1] = strcmp((*command)[i], "'") ? q[1] : !q[1];
    if (!strcmp((*command)[i], "`"))
    {
      j = get_match_quote(*command, i);
      sub_command = get_sub_tab(*command, i + 1, j - i - 1);
      if (!q[0] && !q[1] && (new_command = exec_backquote(&sub_command, sh)))
	*command = insert_tab_in_tab(*command, new_command, i, j - i + 1);
      else if ((q[0] || q[1]) && (new_line = exec_in_q(&sub_command, sh)))
	*command = insert_str_in_tab(*command, new_line, i, j - i + 1);
      else
	tronc_tab(*command, i, j - i + 1);
      free_backquote(new_command, sub_command);
    }
  }
}
