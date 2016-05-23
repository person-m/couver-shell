/*
** minishell2.c for 42sh in /home/hedia_m/couver-shell/minishell2
** 
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
** 
** Started on  Fri May 20 21:09:32 2016 mohamed-laid hedia
** Last update Sun May 22 21:21:34 2016 mohamed-laid hedia
*/

#include "mo.h"

void		the_execution(char **tab, char **env)
{
  t_command	s;

  s.i = 0;
  if ((s.save[0] = dup(0)) == -1 || (s.save[1] = dup(1)) == -1)
    return ((void)fprintf(2, "%s\n", strerror(errno)));
  while (tab[i] != 0)
    {
      if (next_is_pipe(tab, s.i))
	pipe_executon(tab, env, &s);
      else if (!strcmp(";", tab[s.i]))
	s.i++;
      else
	normal_execution(tab, env, &s);
    }
}
