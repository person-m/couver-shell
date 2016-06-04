/*
** which.c for 42sh in /home/hedia_m/EPITECH/couver-shell/src/minishell2
**
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
**
** Started on  Fri Jun  3 17:45:44 2016 mohamed-laid hedia
** Last update Sat Jun  4 15:06:21 2016 mohamed-laid hedia
*/

#include "mo.h"

int	check_in_path(char *str, char **tab, int o)
{
  char	*tmp;
  int	i;

  i = 0;
  while (tab[i])
    {
      tmp = my_malloc(sizeof(char) * (strlen(tab[i]) + strlen(str) + 2));
      tmp = strcpy(tmp, tab[i]);
      tmp = strcat(tmp, "/");
      tmp = strcat(tmp, str);
      if (!access(tmp, X_OK))
	{
	  write(1, tmp, strlen(tmp));
	  write(1, "\n", 1);
	  if (o == 0)
	    return (1);
	  else
	    o = 2;
	}
      free(tmp);
      i = i + 1;
    }
  return (o);
}

char	**my_path_tab(t_shell *sh)
{
  char	*str_path;
  char	**tab_path;
  int	n;

  n = -1;
  if ((str_path = get_var_env(sh->env, "PATH=")) == NULL)
    {
      n = confstr(_CS_PATH, NULL, (size_t) 0);
      str_path = my_malloc(sizeof(char) * (n + 1));
      confstr(_CS_PATH, str_path, n);
    }
  tab_path = my_str_to_wordtab_pattern(str_path, ":");
  if (n != -1)
    free(str_path);
  if (!tab_path)
    exit(EXIT_FAILURE);
  return (tab_path);
}

int	my_which(char **tab, t_shell *sh)
{
  int	i;
  int	t;
  char	**path;

  i = 0;
  t = 0;
  if (tab_len(tab) == 1)
    return (write(2, "which: Too few arguments.\n", 26) * 0 - 1);
  path = my_path_tab(sh);
  while (tab[++i])
    {
      if (!access(tab[i], X_OK))
	fprintf(stdout, "%s\n", tab[i]);
      else if (is_builtin(tab[i]))
	fprintf(stdout, "%s: shell built-in command\n", tab[i]);
      else if (check_in_path(tab[i], path, 0) == 0)
	t = fprintf(stdout, "%s: Command not found.\n", tab[i]) * 0 - 1;
    }
  free_tab(path);
  return (t);
}

int	my_where(char **tab, t_shell *sh)
{
  int	i;
  int	t;
  char	**path;

  i = 0;
  t = 0;
  if (tab_len(tab) == 1)
    return (write(2, "where: Too few arguments.\n", 26) * 0 - 1);
  path = my_path_tab(sh);
  while (tab[++i])
    {
      if (slash_in_str(tab[i]))
	t = fprintf(stdout, "where: / in command makes no sense\n") * 0 - 1;
      else
	{
	  if (is_builtin(tab[i]))
	    fprintf(stdout, "%s is a shell built-in\n", tab[i]);
	  if (check_in_path(tab[i], path, 1) == 1 && !is_builtin(tab[i]))
	    t = -1;
	}
    }
  free_tab(path);
  return (t);
}
