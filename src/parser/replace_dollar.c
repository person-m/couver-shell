/*
** replace_dollar.c for replace_dollar in /home/riamon_v/rendu/PSU/couver-shell/src/parser
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Sat May 28 19:06:18 2016 vincent riamon
** Last update Thu Jun  2 18:08:45 2016 vincent riamon
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

static int	insert_cmd(char ***cmd, int i, int j, char *tmp)
{
  char		**tmp2;

  tmp2 = lexer(tmp + 1, 0);
  (*cmd)[i][j] = 0;
  (*cmd) = insert_tab_in_tab((*cmd), tmp2, i, 1);
  free_tab(tmp2);
  if (!(*cmd)[0] || !(*cmd)[1])
    return (0);
  return (1);
}

static int	replace_var_env(char ***cmd, t_shell *sh, int mode)
{
  int		ind[2];
  char		*tmp;
  char		*var;

  ind[0] = -1;
  while ((*cmd)[++ind[0]])
    {
      ind[1] = -1;
      while ((*cmd)[ind[0]][++ind[1]])
	if ((*cmd)[ind[0]][ind[1]] == '$')
	  {
	    var = get_var((*cmd)[ind[0]] + ind[1]);
	    if (!strcmp(var + 1, "?") && replace_ret_value(cmd, ind[1], ind[0], sh))
	      break ;
	    if ((tmp = get_var_env((mode == 0 ? sh->env : sh->set),
				   var + 1)) == NULL)
	      return ((mode == 0 ? undef_var(var + 1, &var) : 0));
	    if (!insert_cmd(cmd, ind[0], ind[1], tmp))
	      return (0);
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
