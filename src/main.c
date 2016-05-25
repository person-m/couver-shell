/*
** main.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 00:09:58 2016
** Last update Wed May 25 22:06:46 2016 vincent riamon
*/

#include "shell.h"

bool			check_std_input(t_shell *sh)
{
  char	**cmd;
  char	buffer[1024];
  int	ret;

  sh->prompt->non_canon_mode.c_cc[VMIN] = 0;
  ioctl(0, TCSETS, &sh->prompt->non_canon_mode);
  sh->prompt->non_canon_mode.c_cc[VMIN] = 1;
  ret = read(0, buffer, 1024);
  ioctl(0, TCSETS, &sh->prompt->standard_mode);
  if (!ret)
    return (0);
  buffer[ret - 1] = 0;
  cmd = my_str_to_wordtab_pattern(buffer, " \t");
  update_history(cmd, sh);
  the_execution(cmd, sh);
  return (1);
}

void	loop_42sh(t_shell *sh)
{
  int	lol = 1;
  char	**cmd;

  while (lol)
    {
      loop_prompt(sh->prompt);
      cmd = my_str_to_wordtab_pattern(sh->prompt->line, " \t");
      update_history(cmd, sh);
      the_execution(cmd, sh);

      /* if (!is_a_builtin(cmd[0])) */
      /* 	fork(); */

      /* write(1, prompt->line, strlen(prompt->line)); */

       update_prompt(sh->prompt);
       free_tab(cmd);
    }
}

int		main(__attribute__((unused))int argc,
		     __attribute__((unused))char **argv,
		     char **env)
{
  t_shell	sh;

  if (!(sh.prompt = init_prompt()))
    return (0);

  sh.env = cpy_env(env);
  fill_history(&sh);
  create_alias(&sh);
  create_oldpwd(&sh);

  if (!check_std_input(&sh))
    {
      ioctl(0, TCSETS, &sh.prompt->non_canon_mode);
      loop_42sh(&sh);
      ioctl(0, TCSETS, &sh.prompt->standard_mode);
    }

  free_prompt(sh.prompt);
  free_tab(sh.env);
  free_tab(sh.alias);
  free_tab(sh.history);
  return (0);
}
