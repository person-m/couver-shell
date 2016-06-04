/*
** set_var_env.c for set_var_env in /home/riamon_v/couver-shell/src/history
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Sat Jun  4 15:44:11 2016 vincent riamon
** Last update Sat Jun  4 22:28:54 2016 vincent riamon
*/

#include "shell.h"

void		is_to_large_history(t_shell *sh)
{
  char		*line;
  char		**tmp;

  if (sh->size_hist > 2000)
    {
      line = strdup("history -c");
      tmp = lexer(line, 0);
      fprintf(stderr, "Your history is to large, he was clear automatically.\n");
      do_the_thing(sh, &tmp, 0);
      free(line);
      free_tab(tmp);
    }
}

void		set_var_env(char ***env, char *var, char *value)
{
  int		i;

  i = 0;
  while ((*env) && (*env)[i] && strncmp((*env)[i], var, strlen(var)))
    i = i + 1;
  if (!(*env)[i])
    return ;
  free((*env)[i]);
  (*env)[i] = my_malloc(sizeof(char) * (strlen(var) + strlen(value) + 1));
  strconcat(var, value, (*env)[i]);
}
