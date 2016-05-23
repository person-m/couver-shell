/*
** pipe.c for 42sh in /home/hedia_m/couver-shell
** 
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
** 
** Started on  Sun May 22 21:19:49 2016 mohamed-laid hedia
** Last update Sun May 22 23:32:43 2016 mohamed-laid hedia
*/

#include "mo.h"

void	do_fork(char **tab, char **env, t_command *s, t_pipe *p)
{
  char	**b;
  int	f;

  if ((f = fork()) == -1)
    return ;
  else if (f == 0)
    {
      if ((b = pars_param(tab, s->i)) == NULL)
	exit(-1);
      else
	if (minishell1(b, &env) == -1)
	  exit(-1);
    }
  if (dup2(0, p->save[0]) == -1)
    return ((void)fprintf(2, "%s\n", strerror(errno)))
}

void	last_process(char **tab, char **env, t_command *s, t_pipe *p)
{
  char	**b;

  if (dup2(1, p->save[1]) == -1)
    return ((void)fprintf(2, "%s\n", strerror(errno)));
  if (dup2(p->p[i % 2][0], 0) == -1)
    return ((void)fprintf(2, "%s\n", strerror(errno)));
  s->failed = 1;
  if (is_builtin(tab[s->i]))
    {
      if ((b = pars_param(tab, s->i)) == NULL)
	{
	  s->failed = -1;
	  return ;
	}
      if (minishell1(b, &env) == -1)
	s->failed = -1;
      free(b);
      return ;
    }
  do_fork(tab, env, s, p);
}

void	do_process(char **tab, char **env, t_command *s, t_pipe *p)
{
  int	t;
  char	*b;
  int	f;

  if ((t = fork()) == -1)
    return ;
  else if (t == 0)
    {
      close(p->p[p->i % 2][0]);
      if (dup2(p->p[p->i % 2][1], 1) == -1)
        return ((void)fprintf(2, "%s\n", strerror(errno)));
      if (p->i != 0)
        if (dup2(p->p[p->i % 2 ? 0 : 1][0], 0) == -1)
          return ((void)fprintf(2, "%s\n", strerror(errno)));
      if ((b = pars_param(tab, s->i)) == NULL)
        exit(-1);
      f = minishell1(b, &env);
      f == -1 ? exit(-1) : exit(0);
    }
  close(p->p[p->i % 2][1]);
}

void		pipe_execution(char **tab, char **env, t_command *s)
{
  t_pipe	p;

  p.i = 0;
  while (next_is_pipe(tab, s->i))
    {
      if (pipe(p.p[i % 2]) == -1)
        return ((void)fprintf(2, "%s\n", strerror(errno)));
      do_process(tab, env, s, &p);
      p.i = p.i + 1;
      s->i = s->i + length_param(tab, s->i);
    }
}
