/*
** opt_c.c for opt_c in /home/riamon_v/couver-shell/src/option
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Sun Jun  5 06:08:51 2016 vincent riamon
** Last update Sun Jun  5 06:49:02 2016 vincent riamon
*/

#include "shell.h"

static int	opt_c(char **argv, t_shell *sh)
{
  char		**tmp;

  if (argv[1] != NULL && !strcmp(argv[1], "-c"))
    {
      if (argv[2])
	{
	  tmp = lexer(argv[2], 0);
	  do_the_thing(sh, &tmp, 0);
	  free_tab(tmp);
	}
      return (1);
    }
  return (0);
}

static int	opt_v(char **argv)
{
  if (argv[1] != NULL && !strcmp(argv[1], "--version"))
    {
      printf("couver-shell 1.swag (EPITECH) 2016-06-04\n");
      return (1);
    }
  return (0);
}

int		options(char **argv, t_shell *sh)
{
  int		i;

  i = 0;
  while (argv[++i])
    {
      if (argv[i][0] == '-' && strcmp(argv[i] + 1, "c") &&
	  strcmp(argv[i] + 1, "-version"))
	{
	  fprintf(stderr, "Unknow option: '%s'\n", argv[i]);
	  return (1);
	}
    }
  if (opt_c(argv, sh) || opt_v(argv))
    return (1);
  return (0);
}
