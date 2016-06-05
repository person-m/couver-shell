/*
** fct_cursor.c for  in /home/buffat_b/couver-shell
** 
** Made by Bertrand Buffat
** Login   <buffat_b@epitech.net>
** 
** Started on  Fri Jun  3 11:23:43 2016 Bertrand Buffat
** Last update Sat Jun  4 22:15:14 2016 Bertrand Buffat
*/

#include "shell.h"

void	start_line_cursor(t_shell *sh)
{
  sh->prompt->count_pos = 0;
  aff_prompt(sh->prompt);
}

void	end_line_cursor(t_shell *sh)
{
  sh->prompt->count_pos = sh->prompt->count_char;
  aff_prompt(sh->prompt);
}

void	erase_word(t_shell *sh)
{
  if (!sh->prompt->count_pos)
    return ;
  --sh->prompt->count_pos;
  while (sh->prompt->line[sh->prompt->count_pos] == ' '
	 || sh->prompt->line[sh->prompt->count_pos] == '\t')
    --sh->prompt->count_pos;
  while (sh->prompt->count_pos
	 && sh->prompt->line[sh->prompt->count_pos] != ' '
	 && sh->prompt->line[sh->prompt->count_pos] != '\t'
	 && sh->prompt->line[sh->prompt->count_pos] != '|'
	 && sh->prompt->line[sh->prompt->count_pos] != ';')
    --sh->prompt->count_pos;
  sh->prompt->count_char = sh->prompt->count_pos;
  aff_prompt(sh->prompt);
}

void	move_left_word(t_shell *sh)
{
  if (!sh->prompt->count_pos)
    return ;
  --sh->prompt->count_pos;
  while (sh->prompt->line[sh->prompt->count_pos] == ' '
	 || sh->prompt->line[sh->prompt->count_pos] == '\t')
    --sh->prompt->count_pos;
  while (sh->prompt->count_pos
	 && sh->prompt->line[sh->prompt->count_pos] != ' '
	 && sh->prompt->line[sh->prompt->count_pos] != '\t'
	 && sh->prompt->line[sh->prompt->count_pos] != '|'
	 && sh->prompt->line[sh->prompt->count_pos] != ';')
    --sh->prompt->count_pos;
  aff_prompt(sh->prompt);
}

void	move_right_word(t_shell *sh)
{
  if (sh->prompt->count_pos == sh->prompt->count_char)
    return ;
  ++sh->prompt->count_pos;
  while (sh->prompt->line[sh->prompt->count_pos] == ' '
	 || sh->prompt->line[sh->prompt->count_pos] == '\t')
    ++sh->prompt->count_pos;
  while (sh->prompt->count_pos < sh->prompt->count_char
	 && sh->prompt->line[sh->prompt->count_pos] != ' '
	 && sh->prompt->line[sh->prompt->count_pos] != '\t'
	 && sh->prompt->line[sh->prompt->count_pos] != '|'
	 && sh->prompt->line[sh->prompt->count_pos] != ';')
    ++sh->prompt->count_pos;
  aff_prompt(sh->prompt);
}
