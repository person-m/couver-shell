/*
** replace_dollar.c for replace_dollar in /home/riamon_v/rendu/PSU/couver-shell/src/parser
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Sat May 28 19:06:18 2016 vincent riamon
** Last update Wed Jun  1 14:36:18 2016 vincent riamon
*/

#include "shell.h"

char		**error_history(char *var)
{
  fprintf(stderr, "%s: Event not found.\n", var);
  return (NULL);
}

char		*error_history2()
{
  fprintf(stderr, "Bad ! arg selector.\n");
  return (NULL);
}

static int	undef_var(char *str)
{
  fprintf(stderr, "%s: Undefined variable.\n", str);
  return (0);
}

static int	replace_var_env(char ***cmd, t_shell *sh, int mode)
{
  int		i;
  int		j;
  char		*tmp;

  i = -1;
  while ((*cmd)[++i])
    {
      j = -1;
      while ((*cmd)[i][++j])
	if ((*cmd)[i][j] == '$')
	  {
	    if ((tmp = get_var_env((mode == 0 ? sh->env : sh->set),
				   (*cmd)[i] + j + 1)) == NULL)
	      return ((mode == 0 ? undef_var((*cmd)[i] + j + 1) : 0));
	    (*cmd)[i][j] = 0;
	    (*cmd)[i] = realloc((*cmd)[i], sizeof(char) *
				(strlen((*cmd)[i]) + strlen(tmp)));
	    strconcat((*cmd)[i], tmp + 1, (*cmd)[i]);
	    break ;
	  }
    }
  return (1);
}

int		replace_vars(char ***cmd, t_shell *sh)
{
  int		ret;

  if ((ret = replace_var_env(cmd, sh, 1)) == 0)
    return (replace_var_env(cmd, sh, 0));
  return (ret);
}
