/*
** cursor.c for  in /home/buffat_b/couver-shell/src/prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:56:13 2016
** Last update Tue May 24 23:59:52 2016 
*/

#include "shell.h"

void	move_cursor(t_prompt *prompt, char *buffer)
{
  //left cursor
  if (!(strcmp("\033[D", buffer)) && prompt->count_pos > 0)
    --prompt->count_pos;

  //right cursor
  else if (!(strcmp("\033[C", buffer)) && prompt->count_pos < prompt->count_char)
    ++prompt->count_pos;

  else
    return ;

  aff_prompt(prompt);
}

int	size_of_int(int n)
{
  int   i;

  i = 1;
  while (n > 9)
    {
      ++i;
      n /= 10;
    }
  return (i);
}

void	move_cursor_back(t_prompt *prompt)
{
  char	lol[16];
  int	i;
  int	width;
  int	height;

  width = (prompt->size_prompt + prompt->count_pos) % prompt->nbcols + 1;
  height = prompt->start_line + (prompt->size_prompt + prompt->count_pos) / prompt->nbcols;

  i = -1;

  lol[++i] = 27;
  lol[++i] = '[';

  i += size_of_int(height);
  int_to_str_rec(lol, i, height);

  lol[++i] = ';';
  i += size_of_int(width);
  int_to_str_rec(lol, i, width);

  lol[++i] = 'H';
  lol[++i] = 0;

  write(1, lol, strlen(lol));
}
