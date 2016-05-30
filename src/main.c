/*
** main.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 00:09:58 2016
** Last update Mon May 30 21:19:34 2016 vincent riamon
*/

#include "shell.h"

void	loop_42sh(t_shell *sh)
{
  char	**cmd;
  int	ret;
  int	ret2;

  while (1)
    {
      loop_prompt(sh);
      cmd = lexer(sh->prompt->line);
      ret = replace_var_env(&cmd, sh);
      ret2 = replace_exclam_dot(&cmd, sh);
      update_history(sh);
      if ((ret == 1 && ret2 == 1) &&
	  !check_command(cmd) && !globbing(&cmd))
      	the_execution(cmd, sh);
      update_prompt(sh->prompt);
      free_tab(cmd);
    }
}

void	free_shell(t_shell sh)
{
  free_tab(sh.env);
  free_tab(sh.alias);
  free_tab(sh.history);
}

int		main(__attribute__((unused))int argc,
		     __attribute__((unused))char **argv,
		     char **env)
{
  t_shell	sh;

  /*char		*couv_rc;*/

  /*
  char		*s;
  char		**cmd;
  write(1, "$> ", 3);
  while ((s = get_next_line(0)))
    {
      cmd = lexer(s);
      update_history(cmd, &sh);
       if (!check_command(cmd))
       	the_execution(cmd, &sh);
      write(1, "$> ", 3);
      free_tab(cmd);
      free(s);
    }
  */

  /*if ((couv_rc = couvrc(env)))
    {
      printf("%s\n", couv_rc);
      lexer(couv_rc);
    }
  free(couv_rc); */

  sh.ret = 0;
  sh.env = cpy_env(env);
  fill_history(&sh);
  create_alias(&sh);
  create_oldpwd(&sh);
  if (!isatty(0))
    {
      get_std_input(&sh);
      free_shell(sh);
      return (sh.ret);
    }
  if (!(sh.prompt = init_prompt(env, sh.history)))
    return (0);
  signal_handler();
  loop_42sh(&sh);
  free_prompt(sh.prompt);
  free_shell(sh);
  return (sh.ret);
}
