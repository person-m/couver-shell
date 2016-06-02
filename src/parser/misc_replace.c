/*
** misc_replace.c for misc_replace.c in /home/riamon_v/rendu/PSU/couver-shell/src/parser
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Thu Jun  2 13:31:04 2016 vincent riamon
** Last update Thu Jun  2 13:41:00 2016 vincent riamon
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

char	*get_var(char *str)
{
  char		*tmp;
  int		i;

  i = 0;
  tmp = my_malloc(sizeof(char) * (strlen(str)));
  while (str[i] && str[i] != '"')
    {
      tmp[i] = str[i];
      i = i + 1;
    }
  tmp[i] = 0;
  return (tmp);
}

char	*put_cmd(char **cmd1, char *cmd2)
{
  char		*tmp;
  int		i;
  int		j;

  i = 0;
  j = 0;
  tmp = my_malloc(sizeof(char) * (strlen(*cmd1) + strlen(cmd2) + 2));
  while ((*cmd1)[i])
    {
      tmp[i] = (*cmd1)[i];
      i++;
    }
  while (cmd2[j])
    {
      tmp[i] = cmd2[j];
      i++;
      j++;
    }
  tmp[i] = '"';
  tmp[i + 1] = 0;
  free(*cmd1);
  return (tmp);
}
