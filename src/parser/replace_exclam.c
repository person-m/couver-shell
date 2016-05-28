/*
** replace_case_in_tab.c for replace_case_in_tab in /home/riamon_v/rendu/PSU/couver-shell/src/parse
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Wed May 25 15:34:56 2016 vincent riamon
** Last update Sat May 28 19:07:58 2016 vincent riamon
*/

#include "shell.h"

static char	*get_var_history(char **hist, char *var)
{
  int		nb;
  int		i;

  i = tab_len(hist);
  nb = atoi(var);
  if (var[0] == '!')
    return (hist[i - 1]);
  if (nb == 0)
    {
      while (--i >= 0)
	if (!strncmp(hist[i], var, strlen(var)))
	  return (hist[i]);
      return (error_history(var, 0));
    }
  if (nb > tab_len(hist) || tab_len(hist) + nb <= 0)
    {
      fprintf(stderr, "%d: Event not found.\n",
	      (nb > tab_len(hist) ? nb : tab_len(hist) + nb));
      return (NULL);
    }
  return ((nb < 0) ? hist[i + nb + 1] : hist[nb - 1]);
}

static int	return_error(int i, char **tab, char **hist, int nb)
{
  if (i <= 0)
    {
      error_history(tab[0], 0);
      return (0);
    }
  if (nb > tab_len(hist) || tab_len(hist) + nb <= 0)
    {
      fprintf(stderr, "%d: Event not found.\n",
	      (nb > tab_len(hist) ? nb : tab_len(hist) + nb));
      return (0);
    }
  return (1);
}

static char	*search_wich_case(char *var, char **tab, int arg)
{
  char		**tmp;

  tmp = my_str_to_wordtab_pattern(var, " ");
  if (arg == 0 && strcmp(tab[1], "0"))
    return (!strcmp(tab[1], "*") ? wordtab_in_str(tmp + 1, 1):
	    !strcmp(tab[1], "$") ? tmp[tab_len(tmp) - 1] :
	    !strcmp(tab[1], "^") ? tmp[1] : error_history(NULL, 1));
  return (arg < tab_len(tmp) ? tmp[arg] : error_history(NULL, 1));
}

static char	*get_var_history2(char **hist, char **tab)
{
  int		i;
  int		nb;
  int		arg;

  i = tab_len(hist);
  nb = atoi(tab[0]);
  arg = atoi(tab[1]);
  while (--i > 0 && nb == 0)
    if (!strncmp(hist[i], tab[0], strlen(tab[0])))
      return (search_wich_case(hist[i], tab, arg));
  if (!return_error(i, tab, hist, nb))
    return (NULL);
  return (search_wich_case((nb < 0 ? hist[i + nb + 1] : hist[nb - 1]),
			   tab, arg));
}

void		replace_exclam_dot(char ***cmd, t_shell *sh)
{
  int		i;
  int		j;
  char		**tmp;
  char		*my_line;

  i = -1;
  while ((*cmd)[++i] && (j = -1))
    while ((*cmd)[i][++j])
      {
	if ((*cmd)[i][j] == '!')
	  {
	    tmp = my_str_to_wordtab_pattern((*cmd)[i] + j + 1, ":");
	    my_line = (tab_len(tmp) == 1 ?
		       get_var_history(sh->history, (*cmd)[i] + j + 1) :
		       get_var_history2(sh->history, tmp));
	    if (my_line != NULL)
	      {
		free((*cmd)[i]);
		(*cmd)[i] = strdup(my_line);
	      }
	    free_tab(tmp);
	    break ;
	  }
      }
}
