/*
** cursor.c for  in /home/buffat_b/couver-shell/src/prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:56:13 2016
** Last update Mon May 30 18:02:18 2016 Bertrand Buffat
*/

#include "shell.h"


/* void	save_current_line(t_prompt *prompt) */
/* { */

/*   if (prompt->tmp_history != NULL) */
/*     free(prompt->tmp_history); */

/*   if (prompt->tmp_history = malloc(sizeof(char) * prompt->count_char)) */
/*     return ; */

/* } */

void	move_cursor(t_prompt *prompt, char *buffer, char **history)
{


  if (!(strcmp(prompt->caps->left, buffer)) && prompt->count_pos > 0)
    --prompt->count_pos;

  else if (!(strcmp(prompt->caps->right, buffer))
	   && prompt->count_pos < prompt->count_char)
    ++prompt->count_pos;

  /* else if (!(strcmp(prompt->caps->up, buffer)) */
  /* 	   && prompt->curr_history > 0) */
  /*   { */
  /*     if (prompt->curr_history == dlen(history) */
  /* 	  save_current_line(prompt); */
            
  /*   } */

  else
    return ;
  (void)history;
  aff_prompt(prompt);
}

void	move_cursor_back(t_prompt *prompt)
{
  char	tab[16];
  int	width;
  int	height;
  int	total_count;

  total_count =
  prompt->size_prompt + prompt->count_pos + (prompt->start_col - 1) +
  size_of_int(prompt->nbr) + size_of_int(prompt-> count_char) + 4;

  width = total_count % prompt->nbcols + 1;
  height = prompt->start_line + total_count / prompt->nbcols;
  fill_tab_caps(tab, height, width);
  write(1, tab, strlen(tab));
}
