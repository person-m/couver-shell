/*
** globbing_misc.c for globbing_misc in /Users/couver_v/Epitech/rendu/couver-shell/src/globbing
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Wed Jun  1 01:33:03 2016 Vincent COUVERCHEL
** Last update Wed Jun  1 01:33:03 2016 Vincent COUVERCHEL
*/

static char	*add_quote(char *str)
{
  char		*new;
  int		size;

  size = strlen(str);
  new = my_malloc((size + 3) * sizeof(char));
  new[0] = '\"';
  strcpy(new + 1, str);
  new[size + 1] = '\"';
  new[size + 2] = 0;
  return (new);
}

static	void	strtabncpy(char **dest, char **src, int n)
{
  int		i;

  i = 0;
  while (i < n && src[i])
  {
    dest[i] = add_quote(src[i]);
    i++;
  }
  dest[i] = NULL;
}

char		**insert_stab_in_tab(char **dest, char **src, int pos, int len)
{
  char		**new;

  if (!(new = malloc(sizeof(char *) * (tablen(dest) + tablen(src) - len + 1))))
    return (NULL);
  wordtabncpy(new, dest, pos);
  strtabncpy(new + pos, src, tablen(src));
  wordtabncpy(new + pos + tablen(src),
	      dest + pos + len, tablen(dest + pos + len));
  free_tab(dest);
  return (new);
}
