/*
** fct_cursor2.c for  in /home/buffat_b/couver-shell
** 
** Made by Bertrand Buffat
** Login   <buffat_b@epitech.net>
** 
** Started on  Sat Jun  4 22:15:00 2016 Bertrand Buffat
** Last update Sat Jun  4 23:17:58 2016 Bertrand Buffat
*/

#include <shell.h>

void	erase_from_cursor_to_beginning(t_shell *sh)
{
  sh->prompt->count_char -= sh->prompt->count_pos;
  memcpy(sh->prompt->line,
  sh->prompt->line + sh->prompt->count_pos,
  sh->prompt->count_char);
  sh->prompt->count_pos = 0;
  aff_prompt(sh->prompt);
}

void	erase_from_cursor_to_end(t_shell *sh)
{
  sh->prompt->count_char -= (sh->prompt->count_char - sh->prompt->count_pos);
}

void	more_complex_string(t_shell *sh, char *buffer)
{

  if (!strcmp("\033[1;5D", buffer))
    move_left_word(sh);

  else if (!strcmp("\033[1;5C", buffer))
    move_right_word(sh);  

}
