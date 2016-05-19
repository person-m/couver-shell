/*
** main.c for main in /home/riamon_v/rendu/PSU/couver-shell/minishell1
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Wed May 18 15:18:36 2016 vincent riamon
** Last update Thu May 19 15:05:47 2016 vincent riamon
*/

#include "my.h"

int		main(int argc, char **argv, char **env)
{
  char		**tab;

  tab = malloc(sizeof(char *) * 5);
  tab[0] = "echo";
  tab[1] = "\033[0;31m";
  tab[2] = "salut";
  tab[3] = "\033[0m";
  tab[4] = NULL;
  my_echo(tab, env);
  /* char		**tmp; */
  /* char		**tab; */

  /* tab = malloc(sizeof(char *) * 5); */
  /* tab[0] = "a"; */
  /* tab[1] = "a"; */
  /* tab[2] = "b"; */
  /* tab[3] = NULL; */
  /* tab[4] = NULL; */
  /* tmp = cpy_env(env); */
  /* my_setenv(tab, &tmp); */
  /* aff_tab(tmp); */
  /* write(1, "\n", 1); */
  /* my_unsetenv(tab, &tmp); */
  /* aff_tab(tmp); */
  /* cmd_cd(tab, tmp); */
  /* free_tab(tmp); */
  return (0);
}
