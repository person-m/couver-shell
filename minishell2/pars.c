/*
** pars.c for 42sh in /home/hedia_m/couver-shell/minishell2
** 
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
** 
** Started on  Fri May 20 21:09:54 2016 mohamed-laid hedia
** Last update Sun May 22 20:56:03 2016 mohamed-laid hedia
*/

#include "mo.h"

int	length_param(char **tab, int i)
{
  int	k;

  k = 0;
  while (tab[i] && !is_sep_param(tab[i]))
    {
      i = i + 1;
      k = k + 1;
    }
  if (tab[i])
    k++;
  return (k);
}

char	**pars_param(char **tab, int i)
{
  char	**b;
  int	k;

  if ((b = malloc(sizeof(char *) * (length_param(tab, i) + 2))) == NULL)
    return (NULL);
  b[k = 0] = 0;
  while (tab[i] && !is_sep_param(tab[i]))
    {
      if (is_redirection(tab[i]))
	{
	  if (change_fd(tab[i], tab[i + 1]) == -1)
	    {
	      free(b);
	      return (NULL);
	    }
	  i = i + 1;
	}
      else
	{
	  b[k++] = tab[i];
          b[k] = 0;
	}
      i++;
    }
  return (b);
}
