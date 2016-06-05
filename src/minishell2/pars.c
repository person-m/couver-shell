/*
** pars.c for 42sh in /home/hedia_m/couver-shell/minishell2
**
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
**
** Started on  Fri May 20 21:09:54 2016 mohamed-laid hedia
** Last update Sun Jun  5 11:11:09 2016 mohamed-laid hedia
*/

#include "mo.h"

int	is_valide(char **tab, t_shell *sh)
{
  char	**path;
  char	*tmp;
  int	i;

  if (is_builtin(tab[0]) || (slash_in_str(tab[0]) && !access(tab[0], X_OK)))
    return (1);
  path = my_path_tab(sh);
  i = -1;
  while (path[++i])
    {
      tmp = my_malloc(sizeof(char) * (strlen(tab[0]) + strlen(path[i]) + 2));
      tmp = strcpy(tmp, path[i]);
      tmp = strcat(tmp, "/");
      tmp = strcat(tmp, tab[0]);
      if (!access(tmp, X_OK))
	{
	  free(tmp);
	  return (1);
	}
      free(tmp);
    }
  return (0);
}

void	pipe_builtin(char **b, t_shell *env, t_pipe *p, t_command *s)
{
  close(p->p[p->i % 2 ? 0 : 1][0]);
  dup2(p->p[p->i % 2 ? 0 : 1][0], 0);
  close(p->p[p->i % 2 ? 0 : 1][0]);
  if (minishell1(b, env) == -1)
    {
      s->failed = -1;
      env->ret = EXIT_FAILURE;
    }
}

int	length_param(char **tab, int i)
{
  int	k;

  k = 0;
  while (tab[i] && !is_sep_param(tab[i]))
    {
      i = i + 1;
      k = k + 1;
    }
  if (tab[i])
    k++;
  return (k);
}

char	**check_redirection(char **tab, char **b, int *i, int *k)
{
  if (is_redirection(tab[*i]))
    {
      if (double_left_redirection(tab[*i], tab[*i + 1]) == -1)
	{
	  free_tab(b);
	  return (NULL);
	}
      *i = *i + 1;
    }
  else
    {
      if (!(b[*k] = malloc(sizeof(char) * (strlen(tab[*i]) + 1))))
	{
	  fprintf(stderr, "%s\n", "Malloc failure!");
	  return (NULL);
	}
      b[*k] = strcpy(b[*k], tab[*i]);
      *k = *k + 1;
      b[*k] = 0;
    }
  return (b);
}

char	**pars_param(char **tab, int i, t_shell *sh)
{
  char	**b;
  int	k;

  if ((b = malloc(sizeof(char *) * (length_param(tab, i) + 2))) == NULL)
    {
      fprintf(stderr, "%s\n", "Malloc failure\n");
      return (NULL);
    }
  b[k = 0] = 0;
  while (tab[i] && !is_sep_param(tab[i]))
    {
      if (!(b = check_redirection(tab, b, &i, &k)))
	return (NULL);
      i++;
    }
  if ((b = alias(b, sh)) == NULL)
    return (NULL);
  return (glob_command(delete_inhibitors(b)));
}
