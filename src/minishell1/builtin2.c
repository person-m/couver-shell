/*
** builtin2.c for builtin2	 in /home/riamon_v/rendu/PSU/couver-shell/minishell1
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Thu May 19 13:56:52 2016 vincent riamon
** Last update Mon May 30 21:16:00 2016 Melvin Personnier
*/

#include "my.h"

int		my_echo(char **tab, __attribute__((unused))t_shell *sh)
{
  int		i;

  i = 0;
  if (tab[1] && !strcmp(tab[1], "-n"))
    i += 1;
  while (tab[++i])
    {
      write(1, tab[i], strlen(tab[i]));
      if (tab[i + 1])
        write(1, " ", 1);
    }
  if ((tab[1] && strcmp(tab[1], "-n")) || !tab[1])
    write(1, "\n", 1);
  return (0);
}

int		my_exit(char **tab, __attribute__((unused))t_shell *sh)
{
  int		nb;

  if ((tab[1] && tab[2] != NULL) || (tab[1] && !my_getnbr(tab[1])))
    {
      fprintf(stderr, "exit: Expression syntax.\n");
      return (-1);
    }
  nb = (!tab[1]) ? 0 : my_getnbr(tab[1]);
  printf("exit\n");
  exit(nb);
  return (0);
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
