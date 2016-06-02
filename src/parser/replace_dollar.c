/*
** replace_dollar.c for replace_dollar in /home/riamon_v/rendu/PSU/couver-shell/src/parser
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Sat May 28 19:06:18 2016 vincent riamon
** Last update Thu Jun  2 14:35:23 2016 vincent riamon
*/

#include "shell.h"

static int	undef_var(char *str, char **var)
{
  fprintf(stderr, "%s: Undefined variable.\n", str);
  free(*var);
  return (0);
}

static int	replace_ret_value(char ***cmd, int j, int i, t_shell *sh)
{
  char		*tmp;

  (*cmd)[i][j] = 0;
  asprintf(&tmp, "%d", sh->ret);
  (*cmd)[i] = put_cmd(&(*cmd)[i], tmp);
  return (1);
}

static int	replace_var_env(char ***cmd, t_shell *sh, int mode)
{
  int		i;
  int		j;
  char		*tmp;
  char		*var;

  i = -1;
  while ((*cmd)[++i])
    {
      j = -1;
      while ((*cmd)[i][++j])
	if ((*cmd)[i][j] == '$')
	  {
	    var = get_var((*cmd)[i] + j);
	    if (!strcmp(var + 1, "?") && replace_ret_value(cmd, j, i, sh))
	      break ;
	    if ((tmp = get_var_env((mode == 0 ? sh->env : sh->set),
				   var + 1)) == NULL)
	      return ((mode == 0 ? undef_var(var + 1, &var) : 0));
	    (*cmd)[i][j] = 0;
	    (*cmd)[i] = put_cmd(&(*cmd)[i], tmp + 1);
	    free(var);
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
