/*
** end_prompt.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 14:25:06 2016
** Last update Wed May 25 14:33:11 2016 
*/

#include "prompt.h"

void	free_prompt(t_prompt *prompt)
{
  free(prompt->line);
  free(prompt->prompt);
  free(prompt->auto_completion);
  free(prompt->final_line);
  free(prompt->caps);
  free(prompt);
}

void	update_prompt(t_prompt *prompt)
{
  //get new line : int and string
  prompt->start_line = get_actual_line(prompt);
  ioctl(0, TCSETS, &prompt->non_canon_mode);
  fill_tab_caps(prompt->start_line_str, prompt->start_line, 1);

  //initialize counters
  prompt->count_char = 0;
  prompt->count_pos = 0;

  //erase buffer
  memset(prompt->final_line, ' ', prompt->nbcols * prompt->nblines - 1);
}
