/*
** set_var_env.c for set_var_env in /home/riamon_v/couver-shell/src/history
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Sat Jun  4 15:44:11 2016 vincent riamon
** Last update Sat Jun  4 15:57:54 2016 vincent riamon
*/

#include "shell.h"

void		set_var_env(char ***env, char *var, char *value)
{
  int		i;

  i = 0;
  while ((*env)[i] && strncmp((*env)[i], var, strlen(var)))
    i = i + 1;
  if (!(*env)[i])
    return ;
  free((*env)[i]);
  (*env)[i] = my_malloc(sizeof(char) * (strlen(var) + strlen(value) + 1));
  strconcat(var, value, (*env)[i]);
}
