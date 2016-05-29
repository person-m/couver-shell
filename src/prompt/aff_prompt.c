/*
** aff_prompt.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 14:05:49 2016
** Last update Fri May 27 17:31:05 2016 
*/

#include "shell.h"

void	erase_down_lines(t_prompt *prompt, int nb_lines)
{
  write(1, prompt->start_line_str, strlen(prompt->start_line_str));
  while (nb_lines >= 0)
    {
      write(1, "\033[K", 3);
      write(1, "\033[B", 3);
      --nb_lines;
    }
  write(1, prompt->start_line_str, strlen(prompt->start_line_str));
}

void	is_out_of_screen(t_prompt *prompt, int nb_lines_buffer)
{
  if (prompt->start_line + nb_lines_buffer > prompt->nblines)
    {
      fill_tab_caps(prompt->start_line_str,  --prompt->start_line, 1);
      write(1, "\n", 1);
    }
}

void	aff_total_line(t_prompt *prompt)
{

  //put prompt
  write(1, "\033[31m", strlen("\033[31m"));
  write(1, prompt->prompt, prompt->size_prompt);
  write(1, "\033[0m", strlen("\033[0m"));

  //put line
  write(1, prompt->line, prompt->count_char);

  //search auto compet
  if (!prompt->size_completion)
    return ;

  //put auto_completion
  write(1, "\033[30;1m", strlen("\033[30;1m"));
  write(1, prompt->auto_completion + (prompt->count_char - prompt->offset),
	prompt->size_completion - (prompt->count_char - prompt->offset));
  write(1, "\033[0m", strlen("\033[0m"));

}

void	aff_prompt(t_prompt *prompt)
{
  int	nb_lines_buffer;

  //line's buffer size
  nb_lines_buffer = (prompt->size_prompt + prompt->count_char + prompt->size_completion)
    / prompt->nbcols;

  //check screen
  is_out_of_screen(prompt, nb_lines_buffer);

  //clear previous characters
  erase_down_lines(prompt, nb_lines_buffer);

  //aff line
  aff_total_line(prompt);

  //move cursor to its place
  move_cursor_back(prompt);
}
