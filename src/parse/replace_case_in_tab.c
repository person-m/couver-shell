/*
** replace_case_in_tab.c for replace_case_in_tab in /home/riamon_v/rendu/PSU/couver-shell/src/parse
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Wed May 25 15:34:56 2016 vincent riamon
** Last update Wed May 25 19:14:48 2016 vincent riamon
*/

#include "shell.h"

void		replace_var_env(char ***cmd, t_shell *sh)
{
  int		i;
  int		j;
  char		*tmp;

  i = -1;
  while ((*cmd)[++i])
    {
      j = -1;
      while ((*cmd)[i][++j])
	{
	  if ((*cmd)[i][j] == '$')
	    {
	      if ((tmp = get_var_env(sh->env, (*cmd)[i] + j + 1)) == NULL)
		{
		  fprintf(stderr, "%s: Undefined variable.\n", (*cmd)[i] + j + 1);
		  return ;
		}
	      free((*cmd)[i]);
	      (*cmd)[i] = strdup(tmp + 1);
	      return ;
	    }
	}
    }
}
