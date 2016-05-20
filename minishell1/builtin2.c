/*
** builtin2.c for builtin2	 in /home/riamon_v/rendu/PSU/couver-shell/minishell1
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Thu May 19 13:56:52 2016 vincent riamon
** Last update Fri May 20 17:47:04 2016 vincent riamon
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

  i = 0;
  if (strcmp(tab[0], "echo") != 0)
    return ;
  if (!strcmp(tab[1], "-n"))
    i += 1;
  while (tab[++i])
    {
      printf("%s", tab[i]);
      if (tab[i + 1])
        printf(" ");
    }
  if (strcmp(tab[1], "-n"))
    printf("\n");
}

void		my_exit(char **tab)
{
  int		nb;

  if (strcmp(tab[0], "exit") != 0)
    return ;
  if (tab[2] || (tab[1] && !my_getnbr(tab[1])))
    {
      fprintf(stderr, "exit: Expression syntax.\n");
      return ;
    }
  nb = (!tab[1]) ? 0 : my_getnbr(tab[1]);
  printf("exit\n");
  exit(nb);
}

void		built_in(char **tab, char ***env)
{
  my_exit(tab);
  my_echo(tab, *env);
  cmd_cd(tab, *env);
  my_setenv(tab, env);
  my_unsetenv(tab, env);
  if (!strcmp(tab[0], "env"))
    aff_tab(*env);
}
