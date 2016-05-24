/*
** main.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:50:43 2016
** Last update Tue May 24 11:50:46 2016 
*/

#include "shell.h"

void	loop_42sh(t_prompt *prompt, t_shell *sh)
{
  int	lol = 1;

  while (lol)
    {
      loop_prompt(prompt);
      write(1, "\n", 1);
      sh->cmd = my_str_to_wordtab_pattern(prompt->line, " \t");
      if (!is_a_builtin(sh->cmd[0]))
	fork();
      minishell1(sh->cmd, &sh->env);
      write(1, prompt->line, strlen(prompt->line));
      update_prompt(prompt);
    }
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

  ioctl(0, TCSETS, &prompt->non_canon_mode);
  loop_42sh(prompt, &sh);
  ioctl(0, TCSETS, &prompt->standard_mode);

  free_prompt(prompt);
  return (0);
}
