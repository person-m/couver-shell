/*
** end_prompt.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 14:25:06 2016
** Last update Sun Jun  5 15:53:54 2016 Bertrand Buffat
*/

#include "shell.h"

void	update_local_prompt(t_prompt *prompt)
{
  get_actual_line(prompt);
  tcsetattr(0, 0, &prompt->non_canon_mode);
  fill_tab_caps(prompt->start_line_str, prompt->start_line, prompt->start_col);
}

void	update_prompt(t_prompt *prompt)
{
  get_pwd_prompt(prompt);
  get_actual_line(prompt);
  tcsetattr(0, 0, &prompt->non_canon_mode);
  fill_tab_caps(prompt->start_line_str, prompt->start_line, prompt->start_col);
  prompt->count_char = 0;
  prompt->count_pos = 0;
  prompt->size_completion = 0;
  prompt->offset = 0;
  prompt->curr_history = dlen(prompt->history);
  ++prompt->nbr;
}

void	fct_clear(t_shell *sh)
{
  write(1, sh->prompt->caps->clear, strlen(sh->prompt->caps->clear));
  fill_tab_caps(sh->prompt->start_line_str, 0, 0);
  write(1, sh->prompt->start_line_str, strlen(sh->prompt->start_line_str));
  update_local_prompt(sh->prompt);
  sh->prompt->ret = 0;
}

void	clear_line(t_prompt *prompt)
{
  int	nb_lines_buffer;
  int	total_count;

  total_count = prompt->size_pwd +
  prompt->size_prompt + prompt->count_char + prompt->count_char +
  size_of_int(prompt->nbr) + size_of_int(prompt->count_char) + 8;
  nb_lines_buffer = total_count / prompt->nbcols;
  erase_down_lines(prompt, nb_lines_buffer + 1);
}

void	clean_screen(t_prompt *prompt)
{
  int	nb_lines_buffer;
  int	total_count;

  total_count = prompt->size_pwd +
  prompt->size_prompt + prompt->count_pos +
  size_of_int(prompt->nbr) + size_of_int(prompt->count_char) + 8;
  nb_lines_buffer = total_count / prompt->nbcols;
  erase_down_lines(prompt, nb_lines_buffer);
  aff_line_prompt(prompt);
  write(1, prompt->line, prompt->count_char);
  write(1, "\n", 1);
}
