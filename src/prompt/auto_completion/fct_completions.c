/*
** fct_completions.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sat May 28 19:01:23 2016
** Last update Mon May 30 22:14:32 2016 Bertrand Buffat
*/

#include "shell.h"

void	put_nbr(int nbr)
{
  char	c;

  if (nbr > 9)
    put_nbr(nbr / 10);
  c = nbr % 10 + '0';
  write(1, &c, 1);
}

int	get_offset(char *line, int pos, int *ret)
{
  int	offset;

  *ret = 0;
  if (--pos < 0)
    return (-1);
  if (line[pos] == ' ' ||
      line[pos] == '\t')
    return (-1);
  while (pos >= 0
	 && line[pos] != ' '
	 && line[pos] != '\t'
	 && line[pos] != '|'
	 && line[pos] != ';')
    --pos;
  offset = pos + 1;
  while (pos >= 0
	 && (line[pos] == ' '
	     || line[pos] == '\t'))
    --pos;
  if (pos < 0)
    return (offset);
  if (line[pos] != ';'
      && line[pos] != '|')
    *ret = 1;
  return (offset);
}

int	get_offset_directory(char *line , int pos)
{
  if (--pos < 0)
    return (-1);
  if (line[pos] == ' ' ||
      line[pos] == '\t')
    return (-1);
  while (pos >= 0
	 && line[pos] != ' '
	 && line[pos] != '\t'
	 && line[pos] != '|'
	 && line[pos] != ';')
    {
      if (line[pos] == '/')
	return (pos + 1);
      --pos;
    }
  return (-1);
}

void	get_path_from_line(t_prompt *prompt, int offset_dir, char *path)
{
  memcpy(path,
  prompt->line + prompt->offset,
  prompt->count_char - prompt->offset);
  path[offset_dir - prompt->offset] = 0;
  prompt->offset = offset_dir;
  if (prompt->offset == prompt->count_char)
    prompt->size_completion = 0;
}
