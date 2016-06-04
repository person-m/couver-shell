/*
** edit_buffer.c for  in /home/buffat_b/couver-shell/src/prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:56:22 2016
** Last update Sat Jun  4 17:20:18 2016 Bertrand Buffat
*/

#include "shell.h"

int	get_n_same_bytes(const char *s1, const char *s2)
{
  int	i;

  if (!*s1 || !*s2)
    return (0);
  i = 0;
  while (*s1 && *s2 && *s1 == *s2)
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
  if ((i = --sh->prompt->count_pos) < 0)
    ++i;
  while (sh->prompt->line[i])
    {
      sh->prompt->line[i] = sh->prompt->line[i + 1];
      ++i;
    }
  sh->prompt->line[--sh->prompt->count_char] = 0;
}

void	realloc_line(t_prompt *prompt)
{
  char	*line;

  prompt->size *= 2;
  if (!(line = malloc(sizeof(char) * prompt->size)))
    exit(0);
  memcpy(line, prompt->line, prompt->count_char);
  free(prompt->line);
  prompt->line = line;

}

void	add_char(t_prompt *prompt, char input)
{
  int	i;

  if ((i = prompt->count_char) >= prompt->size - 50)
    realloc_line(prompt);
  while (i > prompt->count_pos)
    {
      prompt->line[i] = prompt->line[i - 1];
      --i;
    }
  prompt->line[prompt->count_pos++] = input;
  prompt->line[++prompt->count_char] = 0;
}
