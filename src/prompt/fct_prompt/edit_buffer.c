/*
** edit_buffer.c for  in /home/buffat_b/couver-shell/src/prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:56:22 2016
** Last update Wed Jun  1 22:39:53 2016 Bertrand Buffat
*/

#include "shell.h"

int	get_n_same_bytes(const char *s1, const char *s2)
{
  int	i;

  i = 0;
  while (*s1 && *s1 == *s2)
    {
      ++s1;
      ++s2;
      ++i;
    }
  return (i);
}

void	delete_char(t_shell *sh)
{
  int	i;

  if (!sh->prompt->count_char || !sh->prompt->count_pos)
    return ;
  i = --sh->prompt->count_pos;
  while (sh->prompt->line[i])
    {
      sh->prompt->line[i] = sh->prompt->line[i + 1];
      ++i;
    }
  sh->prompt->line[--sh->prompt->count_char] = 0;
}

void	add_char(t_prompt *prompt, char input)
{
  int	i;

  i = prompt->count_char;
  while (i > prompt->count_pos)
    {
      prompt->line[i] = prompt->line[i - 1];
      --i;
    }
  prompt->line[prompt->count_pos++] = input;
  prompt->line[++prompt->count_char] = 0;
}
