/*
** my_if.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Fri Jun  3 00:12:17 2016 Melvin Personnier
** Last update Fri Jun  3 20:20:48 2016 Melvin Personnier
*/

#include "my.h"

static int	tab_len2(char **tab)
{
  int		i;
  int		j;

  i = -1;
  j = 0;
  while (tab[++i])
    {
      if (strcmp(tab[i], "(") != 0 && strcmp(tab[i], ")") != 0)
	j++;
    }
  if (j <= 4)
    fprintf(stderr, "if: Empty if.\n");
  return (j);
}

static int	skip_parenth_one(char **tab, int *i, char **one, int *equal)
{
  while (strcmp(tab[*i], "(") == 0 || strcmp(tab[*i], ")") == 0)
    (*i)++;
  *one = strdup(tab[(*i)++]);
  while (strcmp(tab[*i], "(") == 0 || strcmp(tab[*i], ")") == 0)
    (*i)++;
  if (strcmp(tab[*i], "==") == 0)
    *equal = 0;
  else if (strcmp(tab[*i], "!=") == 0)
    *equal = 1;
  else
    {
      fprintf(stderr, "if: Expression Syntax.\n");
      return (-1);
    }
  (*i)++;
  return (0);
}

static void	skip_parenth_two(char **tab, int *i, char **two)
{
  while (strcmp(tab[*i], "(") == 0 || strcmp(tab[*i], ")") == 0)
    (*i)++;
  *two = strdup(tab[(*i)++]);
  while (strcmp(tab[*i], "(") == 0 || strcmp(tab[*i], ")") == 0)
    (*i)++;
}

static void	exec_for_if_(char **exec, t_shell *sh)
{
  do_the_thing(sh, &exec);
}

int		my_if(char **tab, t_shell *sh)
{
  char		*one;
  char		*two;
  char		*exec;
  int		equal;
  int		i;

  i = 1;
  exec = my_malloc(sizeof(char));
  exec[0] = 0;
  if (tab_len2(tab) <= 4)
    return (-1);
  if (skip_parenth_one(tab, &i, &one, &equal) == -1)
    return (-1);
  skip_parenth_two(tab, &i, &two);
  if (equal == 0 && !strcmp(one, two))
    exec_for_if_(tab + i, sh);
  else if (equal == 1 && strcmp(one, two))
    exec_for_if_(tab + i, sh);
  free(exec);
  return (0);
}
