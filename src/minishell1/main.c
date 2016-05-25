/*
** main.c for main in /home/riamon_v/rendu/PSU/couver-shell/minishell1
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Wed May 18 15:18:36 2016 vincent riamon
** Last update Tue May 24 17:06:19 2016 vincent riamon
*/

#include "my.h"

int		main(__attribute__((unused))int argc,
		     char **argv, char **env)
{
  char		**tab;
  t_shell	sh;

  tab = malloc(sizeof(char *) * 6);
  tab[0] = "setenv";
  tab[1] = "OLDPWD";
  tab[2] = NULL;
  tab[3] = "cd";
  tab[4] = "-";
  tab[5] = NULL;
  sh.env = cpy_env(env);
  sh.history = fill_history(env);
  create_alias(&sh);
  my_setenv(tab, &sh);
  update_history(argv + 1, &sh.history, env);
  minishell1(argv + 1, &sh);
  if (!strcmp(argv[1], "setenv") ||
      !strcmp(argv[1], "unsetenv"))
    aff_tab(sh.env);
  if (!strcmp(argv[1], "cd"))
    {
      printf("PWD= %s\nOLDPWD= %s\n", get_var_env(sh.env, "PWD="),
	     get_var_env(sh.env, "OLDPWD="));
      printf("\n------------------------\n\n");
      cmd_cd(tab + 3, &sh);
      printf("PWD= %s\nOLDPWD= %s\n", get_var_env(sh.env, "PWD="),
	     get_var_env(sh.env, "OLDPWD="));
    }
  free_tab(sh.env);
  free_tab(sh.alias);
  free_tab(sh.history);
  free(tab);
  return (0);
}
