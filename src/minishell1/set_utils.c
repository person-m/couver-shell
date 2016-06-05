/*
** builtin6.c for  in /home/person_m/rendu/PSU/42sh/couver-shell/src/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Thu Jun  2 01:53:03 2016 Melvin Personnier
** Last update Sun Jun  5 07:14:31 2016 Melvin Personnier
*/

#include "my.h"

int		equal_or_not(char **tab, int *i)
{
  int		j;

  j = 0;
  while (tab[*i][j] && tab[*i][j] != '=')
    j++;
  if (tab[*i][j] == '=')
    return (1);
  if (tab[*i] && tab[*i][j] == 0 && tab[*i + 1] &&
      tab[*i + 1][0] == '=' &&
      tab[*i + 1][1] == 0 && tab[*i + 2])
    return (2);
  if (tab[*i] && tab[*i][j] == 0 && tab[*i + 1] &&
      tab[*i + 1][0] == '=' && tab[*i + 1][1] == 0)
    return (3);
  return (4);
}

char		*modif_total(char **tab, int *j)
{
  char		*total;
  int		a;

  a = equal_or_not(tab, j);
  if (a == 2)
    {
      total = my_malloc(sizeof(char) * (strlen(tab[*j]) + strlen(tab[*j + 1])
			       + strlen(tab[*j + 2]) + 1));
      total = strcpy(total, tab[*j]);
      total = strcat(total, tab[*j + 1]);
      total = strcat(total, tab[*j + 2]);
      *j = *j + 2;
    }
  else if (a == 3)
    {
      total = my_malloc(sizeof(char) * (strlen(tab[*j]) +
			       strlen(tab[*j + 1]) + 1));
      total = strcpy(total, tab[*j]);
      total = strcat(total, tab[*j + 1]);
      *j = *j + 1;
    }
  else
    total = my_strdup(tab[*j]);
  return (total);
}

int		verif_for_one(char *str)
{
  if (str && ((str[0] < 'a' || str[0] > 'z') &&
	      (str[0] < 'A' || str[0] > 'Z') && (str[0] >= '0' || str[0] <= '9')
	      && str[0] != '_'))
    {
      fprintf(stderr, "set: Variable name must begin with a letter.\n");
      return (0);
    }
  if (!is_alphanum(str))
    {
      fprintf(stderr, "set: Variable name must contain"
	      " alphanumeric characters.\n");
      return (0);
    }
  return (1);
}

void		free_set(char *one, char *two, char *total)
{
  free(one);
  free(two);
  free(total);
}

int		free_set_return(char *one, char *two, char *total)
{
  free(one);
  free(two);
  free(total);
  return (-1);
}
