/*
** pars.c for 42sh in /home/hedia_m/couver-shell/minishell2
**
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
**
** Started on  Fri May 20 21:09:54 2016 mohamed-laid hedia
** Last update Fri Jun  3 14:52:38 2016 mohamed-laid hedia
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

char	**check_redirection(char **tab, char **b, int *i, int *k)
{
  if (is_redirection(tab[*i]))
    {
      if (double_left_redirection(tab[*i], tab[*i + 1]) == -1)
	{
	  free_tab(b);
	  return (NULL);
	}
      *i = *i + 1;
    }
  else
    {
      if (!(b[*k] = malloc(sizeof(char) * (strlen(tab[*i]) + 1))))
	{
	  fprintf(stderr, "%s\n", "Malloc failure!");
	  return (NULL);
	}
      b[*k] = strcpy(b[*k], tab[*i]);
      *k = *k + 1;
      b[*k] = 0;
    }
  return (b);
}

char	**pars_param(char **tab, int i, t_shell *sh)
{
  char	**b;
  int	k;

  if ((b = malloc(sizeof(char *) * (length_param(tab, i) + 2))) == NULL)
    {
      fprintf(stderr, "%s\n", "Malloc failure\n");
      return (NULL);
    }
  b[k = 0] = 0;
  while (tab[i] && !is_sep_param(tab[i]))
    {
      if (!(b = check_redirection(tab, b, &i, &k)))
	return (NULL);
      i++;
    }
  return (glob_command(delete_inhibitors(alias(b, sh))));
}
