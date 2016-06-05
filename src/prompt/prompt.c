/*
** prompt.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 13:17:48 2016
** Last update Sun Jun  5 15:53:28 2016 Bertrand Buffat
*/

#include "shell.h"
#include "input.h"

void	complex_string(t_shell *sh, char *buffer)
{
  int	i;
  char	**cmd;

  i = -1;
  while (buffer[++i])
    {
      if (buffer[i] == '\n')
	{
	  sh->prompt->line[sh->prompt->count_char] = 0;
	  cmd = lexer(sh->prompt->line, 0);
	  aff_prompt(sh->prompt);
	  write(1, "\n", 1);
	  do_the_thing(sh, &cmd, 0);
	  update_prompt(sh->prompt);
	  aff_prompt(sh->prompt);
	}
      else if (buffer[i] > 0)
	which_input(sh, buffer[i]);
    }
}

char	get_input(t_shell *sh)
{
  char	buffer[2048];
  int	ret;

  ret = read(0, buffer, 2047);
  buffer[ret] = 0;
  if (!ret)
    return (0);
  else if (!buffer[1])
    return (buffer[0]);
  if (buffer[0] == 27)
    {
      move_cursor(sh->prompt, buffer, sh->prompt->history, 1);
      more_complex_string(sh, buffer);
    }
  else
    complex_string(sh, buffer);
  aff_prompt(sh->prompt);
  return (0);
}

void	which_input(t_shell *sh, char input)
{
  char	*ptr;
  int	i;

  i = -1;
  while (list_input[++i].input > 0)
    if (input == list_input[i].input)
      {
	if (list_input[i].ptr)
	  list_input[i].ptr(sh);
	return ;
      }
  if ((ptr = get_range_ascii(sh->prompt->caps->ascii, input)))
    while (*ptr != ':' && *ptr)
      {
	add_char(sh->prompt, *ptr);
	++ptr;
      }
  else
    add_char(sh->prompt, input);
}

void	update_prompt_main_loop(t_shell *sh)
{
  sh->prompt->history = sh->history;
  sh->prompt->env = sh->env;
  sh->prompt->ret = sh->ret;
  if (!sh->prompt->count_char)
    sh->prompt->ret = 0;
  update_prompt(sh->prompt);
}

void	loop_prompt(t_shell *sh)
{
  char	input;

  tcsetattr(0, 0, &sh->prompt->non_canon_mode);
  aff_prompt(sh->prompt);
  while ((input = get_input(sh)) != '\n')
    {
      check_signals(sh);
      if (input)
	{
	  which_input(sh, input);
	  auto_completion(sh);
	  aff_prompt(sh->prompt);
	}
    }
  clean_screen(sh->prompt);
  if (!sh->prompt->count_char)
    --sh->prompt->nbr;
  sh->prompt->line[sh->prompt->count_char] = 0;
  tcsetattr(0, 0, &sh->prompt->standard_mode);
}
