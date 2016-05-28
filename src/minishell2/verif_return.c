/*
** verif_return.c for 42sh in /home/hedia_m/couver-shell/minishell2
**
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
**
** Started on  Mon May 23 11:00:07 2016 mohamed-laid hedia
** Last update Sat May 28 14:37:03 2016 mohamed-laid hedia
*/

#include "mo.h"

int	verif_one_sig(int st, t_command *s)
{
  if (WIFSIGNALED(st))
    {
      s->failed = -1;
      if (WTERMSIG(st) == SIGSEGV)
	fprintf(stderr, "%s", "Segmentation fault");
      else if (WTERMSIG(st) == SIGFPE)
	fprintf(stderr, "%s", "Floating exception");
      if (WCOREDUMP(st))
	fprintf(stderr, "%s", " (coredumped) ");
      fprintf(stderr, "%c", '\n');
      return (WTERMSIG(st) + 128);
    }
  if (WIFEXITED(st) && WEXITSTATUS(st) != 0)
    s->failed = -1;
  return (WEXITSTATUS(st));
}

int	verif_sig(int st, int *t, t_command *s)
{
  if (WIFSIGNALED(st))
    {
      if (*t == 1)
	*t = 3;
      s->failed = -1;
      if (WTERMSIG(st) == SIGSEGV && *t != 2)
	{
	  fprintf(stderr, "%s", "Segmentation fault");
	  *t = 2;
	}
      else if (WTERMSIG(st) == SIGFPE && *t != 2)
      {
	fprintf(stderr, "%s", "Floating exception");
	*t = 2;
      }
      if (WCOREDUMP(st))
	{
	  fprintf(stderr, "%s", " (coredumped) ");
	  *t = 2;
	}
      return (128 + WTERMSIG(st));
    }
  return (0);
}

int	verif_ret_pipe(int *f, t_command *s, t_pipe *p, int ret)
{
  int	i;
  int	t;
  int aux;

  i = 0;
  t = 1;
  while (i < p->i)
    {
      aux = verif_sig(f[i], &t, s);
      if (aux)
	ret = aux;
      if (WIFEXITED(f[i]) && WEXITSTATUS(f[i]) != EXIT_SUCCESS)
	{
	  s->failed = -1;
	  ret = WEXITSTATUS(f[i]);
	}
      i = i + 1;
    }
  if (t == 2)
    fprintf(stderr, "%c", '\n');
  free(f);
  return (ret);
}
