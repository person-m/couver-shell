/*
** end_prompt.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 14:25:06 2016
** Last update Sun May 29 03:22:55 2016 
*/

#include "shell.h"

void	update_local_prompt(t_prompt *prompt)
{
  prompt->start_line = get_actual_line(prompt);
  ioctl(0, TCSETS, &prompt->non_canon_mode);
  fill_tab_caps(prompt->start_line_str, prompt->start_line, 1);
}

void	update_prompt(t_prompt *prompt)
{
  prompt->start_line = get_actual_line(prompt);
  ioctl(0, TCSETS, &prompt->non_canon_mode);
  fill_tab_caps(prompt->start_line_str, prompt->start_line, 1);

  prompt->count_char = 0;
  prompt->count_pos = 0;
  prompt->size_completion = 0;
  prompt->offset = 0;
}

void	fct_clear(t_shell *sh)
{
  write(1, sh->prompt->caps->clear , strlen(sh->prompt->caps->clear));
  fill_tab_caps(sh->prompt->start_line_str, 0, 0);
  write(1, sh->prompt->start_line_str, strlen(sh->prompt->start_line_str));
  update_local_prompt(sh->prompt);
}

void	clean_screen(t_prompt *prompt)
{
  int	nb_lines_buffer;

  nb_lines_buffer =
  (prompt->size_prompt + prompt->count_char + prompt->size_completion)
  / prompt->nbcols;

  erase_down_lines(prompt, nb_lines_buffer);

  write(1, "\033[31m", strlen("\033[31m"));
  write(1, prompt->prompt, prompt->size_prompt);
  write(1, "\033[0m", strlen("\033[0m"));

  write(1, prompt->line, prompt->count_char);
  write(1, "\n", 1);
}
