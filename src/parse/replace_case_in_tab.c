/*
** replace_case_in_tab.c for replace_case_in_tab in /home/riamon_v/rendu/PSU/couver-shell/src/parse
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Wed May 25 15:34:56 2016 vincent riamon
** Last update Wed May 25 22:06:26 2016 vincent riamon
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

static char	*get_var_history(char **hist, char *var)
{
  int		nb;
  int		i;

  i = tab_len(hist) - 1;
  nb = atoi(var);
  if (nb == 0)
    {
      while (i > 0)
	{
	  if (!strncmp(hist[i], var, strlen(var)))
	    return (hist[i]);
	  i = i - 1;
	}
      fprintf(stderr, "%s: Event not found.\n", var);
      return (NULL);
    }
  if (nb > tab_len(hist))
    fprintf(stderr, "%d: Event not found.\n", nb);
  else if (tab_len(hist) + nb <= 0)
    {
      fprintf(stderr, "%d: Event not found.\n", tab_len(hist) + nb);
      return (NULL);
    }
  return ((nb < 0) ? hist[i + nb + 1] : hist[nb -1]);
}

void		replace_exclam_dot(char ***cmd, t_shell *sh)
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
	  if ((*cmd)[i][j] == '!')
	    {
	      tmp = get_var_history(sh->history, (*cmd)[i] + j + 1);
	      if (tmp != NULL)
		{
		  free((*cmd)[i]);
		  (*cmd)[i] = strdup(tmp);
		}
	      return ;
	    }
	}
    }
}
