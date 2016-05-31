/*
** builtin4.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Mon May 30 22:36:13 2016 Melvin Personnier
** Last update Tue May 31 19:02:19 2016 Melvin Personnier
*/

#include "my.h"

void		create_set(t_shell *sh)
{
  sh->set = my_malloc(sizeof(char *) * 2);
  sh->set[0] = NULL;
}

static int	print_set(t_shell *sh)
{
  int		i;

  i = -1;
  write(1, "_\t", 2);
  if (tab_len(sh->history) > 1)
    printf("%s\n\n", sh->history[sh->size_hist - 2]);
  else
    printf("\n");
  while (sh->set[++i])
    printf("%s\n", sh->set[i]);
  return (0);
}

int		cmd_set(char **tab, t_shell *sh)
{
  int		i;
  int		bol;

  i = -1;
  bol = 0;
  if (!tab[1])
    return (print_set(sh));
  while (sh->set[++i])
    {
      if (!strncmp(sh->set[i], tab[1], strlen(tab[1])) &&
	  sh->set[i][strlen(tab[1])] == '\t')
	{
	  free(sh->set[i]);
	  sh->set[i] = concat_str(tab[1], tab[2], '\t');
	  bol = 1;
	}
    }
  if (!bol)
    {
      sh->set = realloc(sh->set, ((tab_len(sh->set) + 2) * sizeof(char *)));
      sh->set[i] = concat_str(tab[1], tab[2], '\t');
      sh->set[i + 1] = NULL;
    }
  return (0);
}
