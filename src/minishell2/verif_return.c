/*
** verif_return.c for 42sh in /home/hedia_m/couver-shell/minishell2
** 
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
** 
** Started on  Mon May 23 11:00:07 2016 mohamed-laid hedia
** Last update Tue May 24 17:38:24 2016 mohamed-laid hedia
*/

#include "mo.h"

void	verif_one_sig(int st, t_command *s)
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
    }
  if (WIFEXITED(st) && WEXITSTATUS(st) != 0)
    s->failed = -1;
}

void	verif_sig(int st, int *t, t_command *s)
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
	fprintf(stderr, "%s", " (coredumped) ");
    }
}

void	verif_ret_pipe(int *f, t_command *s, t_pipe *p)
{
  int	i;
  int	t;

  i = 0;
  t = 1;
  while (i < p->i)
    {
      verif_sig(f[i], &t, s);
      if (WIFEXITED(f[i]) && WEXITSTATUS(f[i]) != 0)
	s->failed = -1;
      i = i + 1;
    }
  if (t != 1)
    fprintf(stderr, "%c", '\n');
  free(f);
}
