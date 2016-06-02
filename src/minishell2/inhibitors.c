/*
** inhibitors.c for 42sh in /home/hedia_m/EPITECH/couver-shell/src/minishell2
**
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
**
** Started on  Mon May 30 17:41:19 2016 mohamed-laid hedia
** Last update Thu Jun  2 16:07:58 2016 mohamed-laid hedia
*/

#include "mo.h"

char	*inhibitors_file(char *t)
{
  if (t[0] == '\"')
    {
      t = t + 1;
      t[strlen(t) - 1] = 0;
    }
  return (t);
}

void	delete_strs(char **tab, int i, int j)
{
  i = i + 1;
  j = j + 1;
  while (tab[j] != 0)
    {
      tab[i] = tab[j];
      i = i + 1;
      j = j + 1;
    }
  tab[i] = 0;
}

void	add_to_str(char **tab, int i)
{
  int	j;

  j = i + 1;
  while (tab[j][0] != '\'' && tab[j][0] != '"')
    {
      if (!(tab[i] = realloc(tab[i], (strlen(tab[i]) + strlen(tab[j]) + 1) *
			     sizeof(char))))
	return ;
      tab[i] = strcat(tab[i], tab[j]);
      j = j + 1;
    }
  if (!(tab[i] = realloc(tab[i],
			 (strlen(tab[i]) + strlen(tab[j]) + 1) * sizeof(char))))
    return ;
  strcat(tab[i], tab[j]);
  delete_strs(tab, i, j);
}

char	**delete_inhibitors(char **tab)
{
  int	i;

  i = 0;
  while (tab[i] != 0)
    {
      if ((tab[i][0] == '\'' || tab[i][0] == '\"') && strlen(tab[i]) > 1)
	{
	  tab[i] = tab[i] + 1;
	  tab[i][strlen(tab[i]) - 1] = 0;
	}
      i = i + 1;
    }
  return (tab);
}

void	check_inhibitors(char **tab)
{
  int	i;

  i = 0;
  while (tab[i])
    {
      if (tab[i][0] == '\'' || tab[i][0] == '"')
	add_to_str(tab, i);
      i = i + 1;
    }
}
