/*
** main.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 00:09:58 2016
** Last update Sun Jun  5 15:50:09 2016 Bertrand Buffat
*/

#include "shell.h"

void	do_the_thing(t_shell *sh, char ***cmd, int flag)
{
  if (flag)
  {
    *cmd = insert_str_in_tab(*cmd, "\"", 0, 0);
    *cmd = insert_str_in_tab(*cmd, "\"", tab_len(*cmd), 0);
  }
  if (!check_command(*cmd) &&
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
      is_to_large_history(sh);
      cmd = lexer(sh->prompt->line, 0);
      update_history(sh->prompt->line, sh);
      do_the_thing(sh, &cmd, 0);
      update_prompt_main_loop(sh);
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

int		setting_42sh(t_shell *sh, char **argv, char **env)
{
  sh->ret = 0;
  sh->env = cpy_env(env);
  fill_history(sh);
  create_alias(sh);
  create_oldpwd(sh);
  create_set(sh);
  if (options(argv, sh))
    return (0);
  return (1);
}

int		main(__attribute__((unused))int argc,
		     char **argv,
		     char **env)
{
  t_shell	sh;
  char		**cmd;
  char		*couv_rc;

  if (!setting_42sh(&sh, argv, env))
    return (0);
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
