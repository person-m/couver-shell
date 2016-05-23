/*
** Annex.c for  in /home/buffat_b/42sh_tmp/src
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sat May 14 12:13:47 2016
** Last update Mon May 23 22:33:15 2016 
*/

#include "shell.h"

void	str(char *s)
{
  write(1, s, strlen(s));
}

char	*str_dup(char *s)
{
  char	*d;

  if (!(d = malloc(sizeof(char) * strlen(s) + 1)))
    return (NULL);
  return (strcpy(d, s));
}

char	*str_cat(char *s, char *a)
{
  char	*d;
  int	i;
  int	id;

  if (!(d = malloc(sizeof(char) * strlen(s) + strlen(a) + 1)))
    return (NULL);
  i = -1;
  while (s[++i])
    d[i] = s[i];
  id = 0;
  while (a[id])
    d[i++] = a[id++];
  d[i] = 0;
  free(s);
  free(a);
  return (d);
}

void	int_to_str_rec(char *s, int range, int nbr)
{
  if (nbr > 9)
    int_to_str_rec(s, range - 1, nbr / 10);
  s[range] = nbr % 10 + '0';
}

char	*int_to_str(int nbr)
{
  char	*s;
  int	i;
  int	n;

  i = 1;
  n = nbr;
  while (n > 9)
    {
      ++i;
      n /= 10;
    }
  if (!(s = malloc(sizeof(char) * i + 1)))
    return (NULL);
  s[i] = 0;
  int_to_str_rec(s, i - 1, nbr);
  return (s);
}
