/*
** aff_prompt.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 14:05:49 2016
** Last update Sun Jun  5 03:04:03 2016 Bertrand Buffat
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
      fill_tab_caps(prompt->start_line_str,
      --prompt->start_line, prompt->start_col);
      write(1, "\n", 1);
    }
}

void	aff_line_prompt(t_prompt *prompt)
{
  write(1, "\033[36;1m", strlen("\033[36;1m"));
  write(1, prompt->prompt, prompt->size_prompt);
  write(1, "\033[31;1m", strlen("\033[31;1m"));
  write(1, prompt->pwd, prompt->size_pwd);
  write(1, " ", 1);
  write(1, "\033[32;1m", strlen("\033[32;1m"));
  put_nbr(prompt->count_char);
  write(1, " ", 1);
  write(1, "\033[33;1m", strlen("\033[33;1m"));
  put_nbr(prompt->nbr);
  if (!prompt->ret)
    {
      write(1, "\033[0m", strlen("\033[0m"));
      write(1, " :)", 3);
    }
  else
    {
      write(1, "\033[31;5m", strlen("\033[31;5m"));
      write(1, " :(", 3);
    }
  write(1, "\033[0m", strlen("\033[0m"));
  write(1, "\033[1m", strlen("\033[1m"));
  write(1, " > ", 3);
  write(1, "\033[0m", strlen("\033[0m"));
}

void	aff_total_line(t_prompt *prompt)
{
  aff_line_prompt(prompt);
  write(1, prompt->line, prompt->count_char);
  if (!prompt->size_completion)
    return ;
  write(1, "\033[30;1m", strlen("\033[30;1m"));
  write(1, prompt->auto_completion + (prompt->count_char - prompt->offset),
  prompt->size_completion - (prompt->count_char - prompt->offset));
  write(1, "\033[0m", strlen("\033[0m"));
}

void	aff_prompt(t_prompt *prompt)
{
  int	nb_lines_buffer;
  int	total_count;

  total_count = prompt->size_pwd + prompt->size_completion +
  prompt->size_prompt + prompt->count_char + (prompt->start_col - 1) +
  size_of_int(prompt->nbr) + size_of_int(prompt->count_char) + 8;
  nb_lines_buffer = total_count / prompt->nbcols;
  is_out_of_screen(prompt, nb_lines_buffer);
  erase_down_lines(prompt, nb_lines_buffer);
  aff_total_line(prompt);
  move_cursor_back(prompt);
}
