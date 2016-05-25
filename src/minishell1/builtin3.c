/*
** builtin3.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Tue May 24 15:26:38 2016 Melvin Personnier
** Last update Wed May 25 12:30:46 2016 vincent riamon
*/

#include "my.h"

static int	exit_alias(char **tab, t_shell *sh)
{
  if (tab_len(tab) > 3)
    {
      fprintf(stderr, "alias: Too many arguments.\n");
      return (0);
    }
  if (!tab[1])
    {
      aff_tab(sh->alias);
      return (0);
    }
  if (tab_len(tab) <= 2)
    {
      fprintf(stderr, "alias: Not enought arguments.\n");
      return (0);
    }
  return (1);
}

int		my_alias(char **tab, t_shell *sh)
{
  int		i;
  int		bol;

  i = -1;
  bol = 0;
  if (!exit_alias(tab, sh))
    return (-1);
  while (sh->alias[++i])
    {
      if (!strncmp(sh->alias[i], tab[1], strlen(tab[1])))
	{
	  free(sh->alias[i]);
	  sh->alias[i] = concat_str(tab[1], tab[2], '=');
	  bol = 1;
	}
    }
  if (!bol)
    {
      sh->alias = realloc(sh->alias, ((tab_len(sh->alias) + 2) * sizeof(char *)));
      sh->alias[i] = concat_str(tab[1], tab[2], '=');
      sh->alias[i + 1] = NULL;
    }
  aff_tab_alias(sh->alias);
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

void		create_oldpwd(t_shell *sh)
{
  char		**tab;

  tab = my_malloc(sizeof(char *) * 3);
  tab[0] = "setenv";
  tab[1] = "OLDPWD";
  tab[2] = NULL;
  my_setenv(tab, sh);
  free(tab);
}
