/*
** main.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 00:09:58 2016
** Last update Thu May 26 12:54:41 2016 mohamed-laid hedia
*/

#include "shell.h"

bool			check_std_input(t_shell *sh)
{
  char	buffer[1024];
  char	**cmd;
  int	ret;

  ioctl(0, TCSETS, &sh->prompt->non_canon_mode);
  ret = read(0, buffer, 1024);
  ioctl(0, TCSETS, &sh->prompt->standard_mode);
  if (!ret)
    return (0);
  buffer[ret - 1] = 0;

  //temporary minishell
  cmd = my_str_to_wordtab_pattern(buffer, " \t");
  update_history(cmd, sh);
  the_execution(cmd, sh);
  //end

  return (1);
}

void	loop_42sh(t_shell *sh)
{
  char	**cmd;

  while (2 + 2 == 4)
    {
      loop_prompt(sh);
      cmd = lexer(sh->prompt->line);
      update_history(cmd, sh);
      the_execution(cmd, sh);
      update_prompt(sh->prompt);
      free_tab(cmd);
    }
}

int		main(__attribute__((unused))int argc,
		     __attribute__((unused))char **argv,
		     char **env)
{
  t_shell	sh;

  sh.ret = 0;
  if (!(sh.prompt = init_prompt()))
    return (0);

  sh.env = cpy_env(env);
  fill_history(&sh);
  create_alias(&sh);
  create_oldpwd(&sh);

  signal_handler();

  if (!check_std_input(&sh))
    loop_42sh(&sh);

  free_prompt(sh.prompt);
  free_tab(sh.env);
  free_tab(sh.alias);
  free_tab(sh.history);
  return (sh.ret);
}
