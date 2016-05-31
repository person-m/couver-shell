/*
** backquote_utils.c for backquote_utils in /Users/couver_v/Epitech/rendu/couver-shell/src/backquote
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Tue May 31 01:04:39 2016 Vincent COUVERCHEL
** Last update Tue May 31 01:04:39 2016 Vincent COUVERCHEL
*/

static char	**get_sub_tab(char **tab, int pos, int len)
{
  char		**new;
  int		i;
  
  i = 0;
  if (!(new = malloc(sizeof(char *) * (len + 1))))
    return (NULL);
  while (i < len && tab[pos + i])
  {
    new[i] = strdup(tab[pos + i]);
    i++;
  }
  new[i] = NULL;
  return (new);
}
