/*
** builtin3-2.c for couer-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Sun Jun  5 00:31:42 2016 Melvin Personnier
** Last update Sun Jun  5 00:31:55 2016 Melvin Personnier
*/

#include "my.h"

char	*concat_alias(char **tab)
{
  int	i;
  char	*str;

  str = my_malloc(sizeof(char) * 1);
  str[0] = 0;
  i = 1;
  while (tab[++i])
    {
      if (str[0] != 0)
	str = concat_str(str, tab[i], ' ');
      else
	str = strdup(tab[i]);;
    }
  return (str);
}

void		add_line_alias(t_shell *sh, int i, char *tmp, char **tab)
{
  sh->alias = realloc(sh->alias, ((tab_len(sh->alias) + 2) * sizeof(char *)));
  sh->alias[i] = concat_str(tab[1], tmp, '=');
  sh->alias[i + 1] = NULL;
}
