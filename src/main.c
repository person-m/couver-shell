/*
** main.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 00:09:58 2016
** Last update Sun May 29 04:18:30 2016 
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
      if (!check_command(cmd) && !globbing(&cmd))
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

  while (1)
    {
      loop_prompt(sh);
      cmd = lexer(sh->prompt->line);
      if (!check_command(cmd) && !globbing(&cmd))
	the_execution(cmd, sh);
      update_history(cmd, sh);
      update_prompt(sh->prompt);
      free_tab(cmd);
    }
}

/*void	is_alias(char **s, t_shell sh)
{
  int	i;
  int	a;

  i = -1;
  a = strlen(*s);
  while (sh.alias[++i])
    {
      if (!strncmp(*s, sh.alias[i], a))
	{
	  free(*s);
	  *s = strdup(sh.alias[i] + a + 1);
	}
  }
}*/

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
  if (!(sh.prompt = init_prompt(env)))
    return (0);
  signal_handler();
  loop_42sh(&sh);
  free_prompt(sh.prompt);
  free_shell(sh);
  return (sh.ret);
}
