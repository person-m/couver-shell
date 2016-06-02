/*
** globbing_utils.c for globbing_utils in /Users/couver_v/Epitech/rendu/couver-shell/src/globbing
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Sun May 29 16:54:59 2016 Vincent COUVERCHEL
** Last update Sun May 29 16:54:59 2016 Vincent COUVERCHEL
*/

static int	tablen(char **array)
{
  int		i;

  i = 0;
  while (array && array[i])
    i++;
  return (i);
}

static	void	wordtabncpy(char **dest, char **src, int n)
{
  int		i;

  i = 0;
  while (src && i < n && src[i])
  {
    dest[i] = strdup(src[i]);
    i++;
  }
  dest[i] = NULL;
}
