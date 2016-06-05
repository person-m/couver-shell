/*
** builtin4.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Mon May 30 22:36:13 2016 Melvin Personnier
** Last update Sun Jun  5 03:43:39 2016 Melvin Personnier
*/

#include "my.h"

void		init_one_two(char **one, char **two, char *total)
{
  *one = cut_one(total);
  *two = cut_two(total);
}

void		add_line_set(int i, char *one, char *two, t_shell *sh)
{
  sh->set = realloc(sh->set, ((tab_len(sh->set) + 2) * sizeof(char *)));
  sh->set[i] = concat_str(one, two, '\t');
  sh->set[i + 1] = NULL;
}

void		modif_line(t_shell *sh, int *i, char *one, char *two)
{
  while (sh->set[++(*i)])
    {
      if (!strncmp(sh->set[*i], one, strlen(one)) &&
	  sh->set[*i][strlen(one)] == '\t')
	{
	  free(sh->set[*i]);
	  sh->set[*i] = concat_str(one, two, '\t');
	  sh->bol = 1;
	}
    }
}

int		cmd_set(char **tab, t_shell *sh)
{
  int		i;
  int		j;
  char		*one;
  char		*two;
  char		*total;

  sh->bol = 0;
  j = 0;
  if (!tab[1])
    return (print_set(sh));
  while (tab[++j])
    {
      total = modif_total(tab, &j);
      init_one_two(&one, &two, total);
      if (!verif_for_one(one))
	  return (free_set_return(one, two, total));
      i = -1;
      modif_line(sh, &i, one, two);
      if (!sh->bol)
	add_line_set(i, one, two, sh);
      free_set(one, two, total);
    }
  sh->set = my_sort(sh->set);
  return (0);
}

int		my_unset(char **tab, t_shell *sh)
{
  int		i;
  int		j;

  j = 0;
  if (!tab[1])
    {
      fprintf(stderr, "unset: Too few arguments.\n");
      return (-1);
    }
  while (tab[++j])
    {
      i = is_already_in_set(sh->set, tab[j]);
      while (sh->set[i] && sh->set[i + 1])
	{
	  sh->set[i] = sh->set[i + 1];
	  i = i + 1;
	}
      sh->set[i] = NULL;
    }
  return (0);
}
