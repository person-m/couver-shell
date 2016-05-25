/*
** main.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 00:09:58 2016
** Last update Wed May 25 12:41:48 2016 vincent riamon
*/

#include "shell.h"

void	loop_42sh(t_prompt *prompt, t_shell *sh)
{
  int	lol = 1;
  char	**cmd;

  while (lol)
    {
      loop_prompt(prompt);

      cmd = my_str_to_wordtab_pattern(prompt->line, " \t");
      update_history(cmd, &sh->history, sh->env);
      the_execution(cmd, sh);
      /* if (!is_a_builtin(cmd[0])) */
      /* 	fork(); */

      /* write(1, prompt->line, strlen(prompt->line)); */

      update_prompt(prompt);
    }
  (void)sh;(void)cmd;
}

int		main(__attribute__((unused))int argc,
		     __attribute__((unused))char **argv,
		     char **env)
{
  t_prompt	*prompt;
  t_shell	sh;


  if (!(prompt = init_prompt()))
    return (0);

  sh.env = cpy_env(env);
  sh.history = fill_history(env);
  create_alias(&sh);
  create_oldpwd(&sh);

  ioctl(0, TCSETS, &prompt->non_canon_mode);

  loop_42sh(prompt, &sh);


  ioctl(0, TCSETS, &prompt->non_canon_mode);
  loop_42sh(prompt, &sh);

  ioctl(0, TCSETS, &prompt->standard_mode);

  free_prompt(prompt);
  free_tab(sh.env);
  free_tab(sh.alias);
  free_tab(sh.history);
  return (0);
}
