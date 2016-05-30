/*
** prompt.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 13:17:48 2016
** Last update Mon May 30 23:15:00 2016 Bertrand Buffat
*/

#include "shell.h"
#include "input.h"

int	next_range(char *ptr, char tok)
{
  char	*s;

  s = ptr;
  while (*ptr && *ptr != tok)
    ++ptr;
  return (ptr - s);
}

char	*get_range_ascii(char *ascii, char input)
{
  while (strncmp(ascii, &input, next_range(ascii, ',')))
    {
      ascii += next_range(ascii, ':');
      if (!*ascii)
	return (NULL);
      ++ascii;
    }
  return (ascii + next_range(ascii, ',') + 1);
}

char	get_input(t_prompt *prompt)
{
  char	buffer[1024];
  int	ret;

  ret = read(1, buffer, 1024);
  buffer[ret] = 0;

  if (!ret)
    return (0);
  else if (!buffer[1])
    return (buffer[0]);

  move_cursor(prompt, buffer, prompt->history);

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

void	loop_prompt(t_shell *sh)
{
  char	input;

  tcsetattr(0, 0, &sh->prompt->non_canon_mode);
  aff_prompt(sh->prompt);
  while ((input = get_input(sh->prompt)) != '\n')
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
