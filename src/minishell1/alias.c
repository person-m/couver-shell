/*
** builtin3.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Tue May 24 15:26:38 2016 Melvin Personnier
** Last update Sun Jun  5 21:28:23 2016 Melvin Personnier
*/

#include "my.h"

static int	exit_alias(char **tab, t_shell *sh)
{
  if (!tab[1])
    {
      aff_tab_alias(sh->alias);
      return (0);
    }
  if (tab_len(tab) <= 2)
    {
      if (is_alias(tab + 1, sh))
	printf("%s\n", tab[1]);
      return (1);
    }
  if (strcmp(tab[1], "alias") == 0)
  {
    fprintf(stderr, "alias: Too dangerous to alias that.\n");
    return (0);
  }
  return (1);
}

int		my_alias(char **tab, t_shell *sh)
{
  int		i;
  int		bol;
  char		*tmp;

  i = -1;
  bol = 0;
  if (!exit_alias(tab, sh))
    return (-1);
  if (tab_len(tab) < 3)
    return (0);
  tmp = concat_alias(tab);
  while (sh->alias[++i])
    {
      if (!strncmp(sh->alias[i], tab[1], strlen(tab[1]))
	  && sh->alias[i][strlen(tab[1])] == '=')
	{
	  free_my_alias(sh, i, &bol);
	  sh->alias[i] = concat_str(tab[1], tmp, '=');
	}
    }
  if (!bol)
    add_line_alias(sh, i, tmp, tab);
  sh->alias = my_sort(sh->alias);
  free (tmp);
  return (0);
}

void	        aff_tab_alias(char **tab)
{
  int		i;
  int		j;

  i = -1;
  j = -1;
  while (tab[++i])
    {
      j = -1;
      while (tab[i][++j])
	{
	  printf("%c", tab[i][j]);
          if (tab[i][j] == '=')
	    printf("\'");
	}
      printf("\'");
      printf("\n");
    }
}

void		create_alias(t_shell *sh)
{
  sh->alias = my_malloc(sizeof(char *) * 2);
  sh->alias[0] = NULL;
}

int		is_alias(char **s, t_shell *sh)
{
  int		i;
  int		a;

  i = -1;
  a = strlen(*s);
  while (sh->alias[++i])
    {
      if (!strncmp(*s, sh->alias[i], a) && sh->alias[i][a] == '=')
	{
	  *s = my_strdup(sh->alias[i] + a + 1);
	  return (1);
	}
    }
  return (0);
}
