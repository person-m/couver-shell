/*
** replace_case_in_tab.c for replace_case_in_tab in /home/riamon_v/rendu/PSU/couver-shell/src/parse
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Wed May 25 15:34:56 2016 vincent riamon
** Last update Wed May 25 15:36:28 2016 vincent riamon
*/

#include "shell.h"

void		replace_var_env(char ***cmd, t_shell *sh)
{
  int		i;
  char		*tmp;

  i = -1;
  while ((*cmd)[++i])
    {
      if ((*cmd)[i][0] == '$')
	{
	  if ((tmp = get_var_env(sh->env, (*cmd)[i] + 1)) == NULL)
	    {
	      fprintf(stderr, "%s: Undefined variable.\n", (*cmd)[i] + 1);
	      return ;
	    }
	  free((*cmd)[i]);
	  (*cmd)[i] = strdup(tmp + 1);
	  return ;
	}
    }
}
