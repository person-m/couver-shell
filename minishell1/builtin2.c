/*
** builtin2.c for builtin2	 in /home/riamon_v/rendu/PSU/couver-shell/minishell1
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Thu May 19 13:56:52 2016 vincent riamon
** Last update Thu May 19 15:15:23 2016 vincent riamon
*/

#include "my.h"

void		verif_cd(char **tab, char **env)
{
  struct stat	s;

  s.st_mode = 0;
  stat(tab[1], &s);
  fprintf(stderr, "%s: ", tab[1]);
  if (S_ISDIR(s.st_mode))
    fprintf(stderr, "Permissions denied.\n");
  else if (stat(tab[1], &s) == -1)
    fprintf(stderr, "No such file or directory.\n");
  else if (S_ISREG(s.st_mode))
    fprintf(stderr, "Not a directory.\n");
}

void		my_echo(char **tab, char **env)
{
  int		i;
  int		bol;

  i = 0;
  bol = 0;
  if (!strcmp(tab[1], "-n"))
    {
      i += 1;
      bol = 1;
    }
  while (tab[++i])
    {
      if (tab[i][0] == '$')
	printf("%s", get_var_env(env, tab[i] + 1));
      else
        printf("%s", tab[i]);
      if (tab[i + 1])
        printf(" ");
    }
  if (bol == 0)
    printf("\n");
}
