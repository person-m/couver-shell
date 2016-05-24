/*
** cursor.c for  in /home/buffat_b/42sh_tmp
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Mon May 23 19:06:33 2016
** Last update Mon May 23 23:46:43 2016 
*/

#include "shell.h"

void	move_cursor(t_prompt *prompt, char *buffer)
{
  int	i;

  //left cursor
  if (!(strcmp("\033[D", buffer)) && prompt->count_pos > 0)
    {
      if ((prompt->size_prompt + prompt->count_pos) % prompt->nbcols)
	write(1, "\033[D", 3);
      else
	{
	  write(1, "\033[A", 3);
	  i = prompt->nbcols;
	  while (--i >= 0)
	    write(1, "\033[C", 3);
	}
      --prompt->count_pos;
    }

  //right cursor
  if (!(strcmp("\033[C", buffer)) && prompt->count_pos < prompt->count_char)
    {
      if ((prompt->size_prompt + prompt->count_pos + 1) % prompt->nbcols)
	write(1, "\033[C", 3);
      else
	{
	  write(1, "\033[B", 3);
	  i = prompt->nbcols;
	  while (--i >= 0)
	    write(1, "\033[D", 3);
	}
      ++prompt->count_pos;
    }
}

void	move_cursor_back(t_prompt *prompt)
{
  int	i;

  i = prompt->count_char;
  while (i > prompt->count_pos)
    {
      write(1, "\033[D", 3);
      --i;
    }
}
