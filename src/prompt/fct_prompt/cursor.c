/*
** cursor.c for  in /home/buffat_b/couver-shell/src/prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:56:13 2016
** Last update Fri Jun  3 15:40:53 2016 Bertrand Buffat
*/

#include "shell.h"

void	save_current_line(t_prompt *prompt)
{
  if (prompt->tmp_history != NULL)
    free(prompt->tmp_history);
  if (!(prompt->tmp_history = malloc(sizeof(char) * prompt->count_char + 1)))
    return ;
  memcpy(prompt->tmp_history, prompt->line, prompt->count_char);
  prompt->tmp_history[prompt->count_char] = 0;
}

void	move_history_up(t_prompt *prompt, char **history)
{
  if (prompt->curr_history == dlen(history))
    save_current_line(prompt);
  clear_line(prompt);
  --prompt->curr_history;
  while (prompt->count_char > 0
  	 && prompt->curr_history > 0
	 && !strncmp(prompt->line,
		     history[prompt->curr_history], prompt->count_char))
    --prompt->curr_history;
  memcpy(prompt->line, history[prompt->curr_history],
  strlen(history[prompt->curr_history]));
  prompt->count_char = strlen(history[prompt->curr_history]);
  prompt->count_pos = prompt->count_char;
}

void	move_history_down(t_prompt *prompt, char **history)
{
  int	max_hist;

  max_hist = dlen(history);
  clear_line(prompt);
  ++prompt->curr_history;
  while (prompt->curr_history < max_hist
	 && prompt->count_char > 0
	 && !strncmp(prompt->line,
		     history[prompt->curr_history], prompt->count_char))
    ++prompt->curr_history;
  if (prompt->curr_history == dlen(history))
    {
      memcpy(prompt->line, prompt->tmp_history, strlen(prompt->tmp_history));
      prompt->count_char = strlen(prompt->tmp_history);
    }
  else
    {
      memcpy(prompt->line, history[prompt->curr_history],
      strlen(history[prompt->curr_history]));
      prompt->count_char = strlen(history[prompt->curr_history]);
    }
  prompt->count_pos = prompt->count_char;
}

void	move_cursor(t_prompt *prompt, char *buffer, char **history, char flag)
{
  if (!(strcmp(prompt->caps->left, buffer)) && prompt->count_pos > 0)
    --prompt->count_pos;
  else if (!(strcmp(prompt->caps->right, buffer))
	   && prompt->count_pos < prompt->count_char)
    ++prompt->count_pos;
  else if (flag && !(strcmp(prompt->caps->up, buffer))
  	   && prompt->curr_history > 0)
    move_history_up(prompt, history);
  else if (flag && !(strcmp(prompt->caps->down, buffer))
  	   && prompt->curr_history < dlen(history))
    move_history_down(prompt, history);
}

void	move_cursor_back(t_prompt *prompt)
{
  char	tab[16];
  int	width;
  int	height;
  int	total_count;

  total_count = prompt->size_pwd +
  prompt->size_prompt + prompt->count_pos + (prompt->start_col - 1) +
  size_of_int(prompt->nbr) + size_of_int(prompt-> count_char) + 5;
  width = total_count % prompt->nbcols + 1;
  height = prompt->start_line + total_count / prompt->nbcols;
  fill_tab_caps(tab, height, width);
  write(1, tab, strlen(tab));
}
