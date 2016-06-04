/*
** main.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 00:09:58 2016
** Last update Sat Jun  4 19:40:43 2016 Bertrand Buffat
*/

#include "shell.h"

void	do_the_thing(t_shell *sh, char ***cmd, int flag)
{
  if (flag)
  {
    *cmd = insert_str_in_tab(*cmd, "\"", 0, 0);
    *cmd = insert_str_in_tab(*cmd, "\"", tab_len(*cmd), 0);
  }
  if (!check_command(*cmd) && !replace_variables(cmd, sh) &&
      replace_exclam_dot(cmd, sh) == 1 && !man_couver(*cmd, sh))
  {
    backquote(cmd, sh);
    the_execution(*cmd, sh);
    del_quote(*cmd);
  }
}

void	loop_42sh(t_shell *sh)
{
  char	**cmd;

  while (1)
    {
      loop_prompt(sh);
      cmd = lexer(sh->prompt->line, 0);
      update_history(sh->prompt->line, sh);
      do_the_thing(sh, &cmd, 0);
      sh->prompt->history = sh->history;
      sh->prompt->env = sh->env;
      update_prompt(sh->prompt);
      free_tab(cmd);
    }
}

void	free_shell(t_shell sh)
{
  free_tab(sh.set);
  free_tab(sh.env);
  free_tab(sh.alias);
  free_tab(sh.history);
}

int		main(__attribute__((unused))int argc,
		     __attribute__((unused))char **argv,
		     char **env)
{
  t_shell	sh;
  char		**cmd;
  char		*couv_rc;

  sh.ret = 0;
  sh.env = cpy_env(env);
  fill_history(&sh);
  create_alias(&sh);
  create_oldpwd(&sh);
  create_set(&sh);

  if ((couv_rc = couvrc(env)))
  {
    cmd = lexer(couv_rc, 0);
    do_the_thing(&sh, &cmd, 0);
    free(couv_rc);
  }
  if (!isatty(0))
    {
      get_std_input(&sh);
      free_shell(sh);
      return (sh.ret);
    }
  if (!(sh.prompt = init_prompt(sh.env, sh.history)))
    return (0);

  signal_handler();
  loop_42sh(&sh);
  free_prompt(sh.prompt);
  free_shell(sh);
  return (sh.ret);
}
