/*
** utils.c for utils.c in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Wed May 18 15:46:12 2016 Melvin Personnier
** Last update Fri May 20 16:38:05 2016 vincent riamon
*/

#include "my.h"

void	*my_malloc(int size)
{
  void	*ptr;

  ptr = malloc(size);
  if (ptr == NULL)
    {
      fprintf(stderr, "malloc failure!\n");
      exit(1);
    }
  return (ptr);
}

void		strconcat(const char *s1, const char *s2, char *s3)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (s1[i])
    {
      s3[i] = s1[i];
      i++;
    }
  while (s2[j])
    s3[i++] = s2[j++];
  s3[i] = 0;
}

int		tab_len(char **tab)
{
  int		i;

  i = -1;
  while (tab[++i]);
  return (i);
}

void		free_tab(char **tab)
{
  int		i;

  i = -1;
  while (tab[++i])
    free(tab[i]);
  free(tab);
}

int	my_getnbr(const char *str)
{
  int   div;
  int   i;
  int   nb;

  nb = 0;
  div = 1;
  i = 0;
  while ((str[i] >= 48 && str[i] <= 57)
         || str[i] == 45 || str[i] == 43)
    i = i + 1;
  while (--i >= 0)
    {
      if (str[i] == 45 || (nb < 0 && str[i] == 45))
	nb = nb * -1;
      else if (str[i] >= 48 && str[i] <= 57)
	nb = nb + ((str[i] - 48) * div);
      div = div * 10;
    }
  return (nb);
}
