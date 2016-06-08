/*
** variables.c for variables in /Users/couver_v/Desktop/couver-shell/src/variables
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Fri Jun  3 16:45:02 2016 Vincent COUVERCHEL
** Last update Sat Jun  4 15:39:44 2016 vincent riamon
*/

#include "shell.h"
#include "variables_utils.c"

char	*get_total_id(char *start, char *end)
{
  char 	*new;

  if (!(new = malloc(sizeof(char) * (strlen(start) + strlen(end) + 1))))
    exit(-1);
  strcpy(new, start);
  strcat(new, end);
  return (new);
}

char	*get_value(char *name, t_shell *sh)
{
  char	*value;
  char	**arg;
  char	*tmp;

  if (!strcmp(name, "?"))
    {
      value = my_malloc(sizeof(char) * (nb_digit(sh->ret) + 1));
      sprintf(value, "%d", sh->ret);
      return (value);
    }
  if (!strcmp(name, "#"))
    {
      arg = my_str_to_wordtab_pattern(sh->history[sh->size_hist - 2], " ");
      value = my_malloc(sizeof(char) * (nb_digit(tab_len(arg) - 1) + 1));
      sprintf(value, "%d", tab_len(arg) - 1);
      free_tab(arg);
      return (value);
    }
  value = get_var_env(sh->set, (tmp = get_total_id(name, "\t")));
  free(tmp);
  if (value)
    return (value);
  value = get_var_env(sh->env, (tmp = get_total_id(name, "=")));
  free(tmp);
  return (value);
}

char	*insert_str_in_str(char *dest, char *src, int pos, int len)
{
  char	*new;

  if (!(new = malloc(sizeof(char) * (strlen(dest) + strlen(src) - len + 3))))
    exit(-1);
  strncpy(new, dest, pos);
  if (src)
    strcpy(new + pos, src);
  strcpy(new + pos + strlen(src),
	      dest + pos + len);
  new[strlen(dest) + strlen(src) - len] = 0;
  return (new);
}

char	**replace_variable(char *cmd, t_shell *sh)
{
  char 	**value;
  char	*end;
  char	*ret;
  char	*name;

  cmd++;
  cmd[strlen(cmd) - 1] = 0;
  name = get_variable_name(cmd, &end);
  if (!end)
    return (NULL);
  if (!(ret = get_value(name, sh)))
    return ((char **)(long)
	    (!fprintf(stderr, "%s: Undefined variable.\n", name) && 0));
  value = lexer(ret, 0);
  if (!value[0])
    value = riamon_str_concatstr(cmd, end);
  else
  {
    value[0] = insert_str_in_str(value[0], cmd, 1, 0);
    value[tab_len(value) - 1] =
    insert_str_in_str(value[tab_len(value) - 1],
		      end, strlen(value[tab_len(value) - 1]) - 1, 0);
  }
  return (value);
}

int	replace_variables(char ***cmd, t_shell *sh)
{
  int	i;
  char	**value;

  i = 0;
  while ((*cmd)[i])
  {
    if (is_variable((*cmd)[i]))
    {
      if (!(value = replace_variable((*cmd)[i], sh)))
	return (1);
      *cmd = insert_tab_in_tab(*cmd, value, i, 1);
    }
    i++;
  }
  return (0);
}

