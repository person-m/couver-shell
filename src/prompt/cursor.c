/*
** cursor.c for  in /home/buffat_b/couver-shell/src/prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:56:13 2016
** Last update Wed May 25 14:04:07 2016 
*/

#include "shell.h"

void	move_cursor(t_prompt *prompt, char *buffer)
{

  //left cursor
  if (!(strcmp(prompt->caps->left, buffer)) && prompt->count_pos > 0)
    --prompt->count_pos;

  //right cursor
  else if (!(strcmp(prompt->caps->right, buffer)) && prompt->count_pos < prompt->count_char)
    ++prompt->count_pos;

  else
    return ;

  aff_prompt(prompt);
}

void	move_cursor_back(t_prompt *prompt)
{
  char	tab[16];
  int	width;
  int	height;

  width = (prompt->size_prompt + prompt->count_pos) % prompt->nbcols + 1;
  height = prompt->start_line + (prompt->size_prompt + prompt->count_pos) / prompt->nbcols;

  //get cursor pos and print it
  fill_tab_caps(tab, height, width);
  write(1, tab, strlen(tab));
}
