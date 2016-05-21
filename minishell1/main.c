/*
** main.c for main in /home/riamon_v/rendu/PSU/couver-shell/minishell1
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Wed May 18 15:18:36 2016 vincent riamon
** Last update Sat May 21 14:57:51 2016 Melvin Personnier
*/

#include "my.h"

int		main(__attribute__((unused))int argc,
		     char **argv, char **env)
{
  char		**tab;
  char		**tmp;

  tab = malloc(sizeof(char *) * 6);
  tab[0] = "setenv";
  tab[1] = "OLDPWD";
  tab[2] = NULL;
  tab[3] = "cd";
  tab[4] = "-";
  tab[5] = NULL;
  tmp = cpy_env(env);
  my_setenv(tab, &tmp);
  minishell1(argv + 1, &tmp);
  if (!strcmp(argv[1], "setenv") ||
      !strcmp(argv[1], "unsetenv"))
    aff_tab(tmp);
  if (!strcmp(argv[1], "cd"))
    {
      printf("PWD= %s\nOLDPWD= %s\n", get_var_env(tmp, "PWD="),
	     get_var_env(tmp, "OLDPWD="));
      printf("\n------------------------\n");
      cmd_cd(tab + 3, &tmp);
      printf("PWD= %s\nOLDPWD= %s\n", get_var_env(tmp, "PWD="),
	     get_var_env(tmp, "OLDPWD="));
    }
  free_tab(tmp);
  /* free_tab(tab); */
  return (0);
}
