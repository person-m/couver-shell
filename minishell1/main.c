/*
** main.c for main in /home/riamon_v/rendu/PSU/couver-shell/minishell1
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Wed May 18 15:18:36 2016 vincent riamon
** Last update Fri May 20 21:29:07 2016 Melvin Personnier
*/

#include "my.h"

int		main(int argc, char **argv, char **env)
{
  char		**tab;
  char		**tmp;

  tab = malloc(sizeof(char *) * 6);
  tab[0] = "setenv";
  tab[1] = "OLDPWD";
  tab[2] = "/home/person_m/rendu";
  tab[3] = NULL;
  tab[4] = "d";
  tab[5] = NULL;
  tmp = cpy_env(env);
  aff_tab(tmp);
  my_setenv(tab, &tmp);
  tab_ptn_fct(argv + 1, &tmp);
  if (!strcmp(argv[1], "setenv") ||
      !strcmp(argv[1], "unsetenv"))
    aff_tab(tmp);
  if (!strcmp(argv[1], "cd"))
    {
      printf("%s\n", get_var_env(tmp, "PWD="));
      printf("%s\n", get_var_env(tmp, "OLDPWD="));
      aff_tab(tmp);
    }
  /* free_tab(tmp); */
  return (0);
}
