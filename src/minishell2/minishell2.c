/*
** minishell2.c for 42sh in /home/hedia_m/couver-shell/minishell2
**
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
**
** Started on  Fri May 20 21:09:32 2016 mohamed-laid hedia
** Last update Fri May 27 00:11:07 2016 mohamed-laid hedia
*/

#include "mo.h"

void	my_process(char **tab, t_shell *env, t_command *s)
{
  char	**b;
  int	f;
  int	st;

  st = 0;
  if ((f = fork()) == -1)
    return ;
  else if (f == 0)
    {
      b = pars_param(tab, s->i);
      if (b == NULL)
	exit(1);
      if (minishell1(b, env) == -1)
	exit(1);
    }
  else
    wait(&st);
  env->ret = verif_one_sig(st, s);
}

void	exec_command(char **tab, t_shell *env, t_command *s)
{
  char	**b;

  s->failed = 1;
  if (is_builtin(tab[s->i]))
    {
      env->ret = 0;
      if ((b = pars_param(tab, s->i)) == NULL)
	{
	  env->ret = 1;
	  s->failed = -1;
	  return ;
	}
      if (minishell1(b, env) == -1)
	{
	  env->ret = 1;
	  s->failed = -1;
	}
      else
	s->failed = 1;
      free(b);
      dup2(s->save[1], 1);
      dup2(s->save[1], 0);
    }
  else
    my_process(tab, env, s);
  s->i = s->i + length_param(tab, s->i);
}

void	check_op(char **tab, t_command *s)
{
  if (s->i > 0)
    {
      if (!strcmp("||", tab[s->i - 1]) && s->failed != -1)
	{
	  while (tab[s->i] &&
		 strcmp(tab[s->i - 1], ";") && strcmp(tab[s->i - 1], "&"))
	    s->i = s->i + length_param(tab, s->i);
	  s->failed = 1;
	}
      else if (!strcmp("&&", tab[s->i - 1]) && s->failed == -1)
	{
	  while (tab[s->i] && strcmp(tab[s->i - 1], ";") &&
		 strcmp(tab[s->i - 1], "&") && strcmp(tab[s->i - 1], "||"))
	    s->i = s->i + length_param(tab, s->i);
	  if (strcmp(tab[s->i - 1], "||"))
	    s->failed = 1;
	}
    }
}

void		the_execution(char **tab, t_shell *env)
{
  t_command	s;

  s.i = 0;
  s.failed = 1;
  if ((s.save[0] = dup(0)) == -1 || (s.save[1] = dup(1)) == -1)
    return ((void)fprintf(stderr, "%s\n", strerror(errno)));
  while (tab[s.i] != 0)
    {
      check_op(tab, &s);
      if (tab[s.i] == 0)
	break ;
      if (next_is_pipe(tab, s.i))
	pipe_execution(tab, env, &s);
      else if (!strcmp(";", tab[s.i]) || !strcmp("&", tab[s.i]))
	{
	  s.failed = 1;
	  s.i++;
	}
      else
	exec_command(tab, env, &s);
      dup2(s.save[0], 0);
      dup2(s.save[1], 1);
    }
}
