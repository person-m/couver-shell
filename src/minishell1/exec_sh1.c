/*
** exec_sh1.c for exec_sh1.c in /home/person_m/rendu/PSU/42sh/couver-shell/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Sat May 21 16:32:56 2016 Melvin Personnier
** Last update Thu Jun  2 01:28:33 2016 Melvin Personnier
*/

#include "my.h"

static int      cmd_not_found(char **tab)
{
  fprintf(stderr, "%s: Command not found.\n", tab[0]);
  return (-1);
}

static int	perm_denied(char **tab)
{
  fprintf(stderr, "%s: Permission denied.\n", tab[0]);
  return (-1);
}

static int	test_path(char **tab, char **env)
{
  int		i;
  char		*path_in_str;
  char		**path_in_array;
  char		*cmd;
  int		a;

  if ((path_in_str = get_var_env(env, "PATH=")) == NULL)
    path_in_str = strdup("/bin");
  path_in_array = my_str_to_wordtab_pattern(path_in_str, ":");
  i = -1;
  while (path_in_array[++i])
    {
      cmd = concat_str(path_in_array[i], tab[0], '/');
      if ((a = execve(cmd, tab, env)) != -1)
	{
	  free(cmd);
	  free_tab(path_in_array);
	  return (a);
	}
      free(cmd);
    }
  free_tab(path_in_array);
  return (cmd_not_found(tab));
}

static int	instant_exec(char **tab, char **env)
{
  int		a;
  int		my_errno;

  a = execve(tab[0], tab, env);
  my_errno = errno;
  if (a == -1)
    {
      if (tab[0][0] == '.')
	{
	  if ((strlen(tab[0]) > 2 && access(tab[0] + 2, X_OK) == -1 &&
	      access(tab[0] + 2, F_OK) != -1) || strlen(tab[0]) <= 2 ||
	      opendir(tab[0] + 2) != NULL)
	    return (perm_denied(tab));
	}
      if (tab[0][0] == '/' && opendir(tab[0]) != NULL)
	return (perm_denied(tab));
      if (my_errno == ENOEXEC)
	fprintf(stderr, "%s: Exec format error. "
		"Binary file not executable.\n", tab[0]);
      else
	fprintf(stderr, "%s: Command not found.\n", tab[0]);
    }
  return (a);
}

int		exec_sh1(char **tab, t_shell *sh)
{
  if (tab[0][0] == '.' || tab[0][0] == '/' || slash_in_str(tab[0]) == 1)
    return (instant_exec(tab, sh->env));
  return (test_path(tab, sh->env));
}
