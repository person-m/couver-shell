/*
** main.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 00:09:58 2016
** Last update Fri May 27 13:59:33 2016 vincent riamon
*/

#include "shell.h"

bool			check_std_input(t_shell *sh)
{
  char	buffer[1024];
  char	**cmd;
  char  **instr;
  int	ret;
  int	i;

  ioctl(0, TCSETS, &sh->prompt->non_canon_mode);
  ret = read(0, buffer, 1024);
  ioctl(0, TCSETS, &sh->prompt->standard_mode);
  if (!ret)
    return (0);

  buffer[ret] = 0;
  instr = my_str_to_wordtab_pattern(buffer, "\n");
  i = 0;
  while (instr[i])
    {
      //temporary minishell
      cmd = lexer(instr[i]);
      update_history(cmd, sh);
      the_execution(cmd, sh);
      //end
      ++i;
    }

  free_tab(instr);
  return (1);
}

void	loop_42sh(t_shell *sh)
{
  char	**cmd;

  while (2 + 2 == 4)
    {
      loop_prompt(sh);
      cmd = lexer(sh->prompt->line);
      if (!check_command(cmd))
	the_execution(cmd, sh);
      update_history(cmd, sh);
      update_prompt(sh->prompt);
      free_tab(cmd);
    }
}

int		main(__attribute__((unused))int argc,
		     __attribute__((unused))char **argv,
		     char **env)
{
  t_shell	sh;
  /*char		*couv_rc;*/

  sh.ret = 0;
  if (!(sh.prompt = init_prompt(env)))
    return (0);

  sh.env = cpy_env(env);
  fill_history(&sh);
  create_alias(&sh);
  create_oldpwd(&sh);

  /*if ((couv_rc = couvrc(env)))
    {
      printf("%s\n", couv_rc);
      lexer(couv_rc);
    }
  free(couv_rc); */

  signal_handler();

  if (!check_std_input(&sh))
    loop_42sh(&sh);

  free_prompt(sh.prompt);
  free_tab(sh.env);
  free_tab(sh.alias);
  free_tab(sh.history);
  return (sh.ret);
}
