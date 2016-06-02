/*
** replace_dollar.c for replace_dollar in /home/riamon_v/rendu/PSU/couver-shell/src/parser
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Sat May 28 19:06:18 2016 vincent riamon
** Last update Fri Jun  3 00:41:14 2016 vincent riamon
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
  int		bol;

  bol = 1;
  tmp2 = lexer(tmp + 1, 0);
  (*cmd)[i][j] = 0;
  (*cmd)[i] = realloc((*cmd)[i], sizeof(char *) * (strlen((*cmd)[i])
						   + strlen(tmp) + 1));
  (*cmd)[i] = put_cmd(&(*cmd)[i], tmp + 1);
  if (tmp2[1] != NULL)
    {
      bol = 0;
      (*cmd) = insert_tab_in_tab((*cmd), tmp2, i, 1);
    }
  free_tab(tmp2);
  if (!(*cmd)[0] || (!(*cmd)[1] && bol != 1))
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

/* static int	replace_var_env(char ***cmd, t_shell *sh, int mode) */
/* { */
/*   int		i; */
/*   int		j; */
/*   char		**tab; */
/*   char		*var; */
/*   int		inc; */

/*   i = -1; */
/*   inc = 1; */
/*   (void)sh; */
/*   while ((*cmd)[++i]) */
/*     { */
/*       j = -1; */
/*       while ((*cmd)[i][++j]) */
/* 	if ((*cmd)[i][j] == '$') */
/* 	  { */
/* 	    tab = my_str_to_wordtab_pattern((*cmd)[i], "{}"); */
/* 	    aff_tab(tab); */
/* 	    if (there_is_accolade((*cmd)[i], &inc) && !tab[2]) */
/* 	      return (error_accolades(mode)); */
/* 	    var = get_var((*cmd)[i] + j + inc); */
/* 	    if (!strcmp(var + 1, "?") && replace_ret_value(cmd, j, i, sh)) */
/* 	      break ; */
/* 	  } */
/*     } */
/*   return (1); */
/* } */

int		replace_vars(char ***cmd, t_shell *sh)
{
  int		ret;

  if ((ret = replace_var_env(cmd, sh, 1)) == 0)
    return (replace_var_env(cmd, sh, 0));
  return (ret);
}
