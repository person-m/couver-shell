/*
** fct_rebind.c for  in /home/buffat_b/couver-shell/src/prompt
** 
** Made by Bertrand Buffat
** Login   <buffat_b@epitech.net>
** 
** Started on  Fri Jun  3 15:27:58 2016 Bertrand Buffat
** Last update Sun Jun  5 03:31:58 2016 Bertrand Buffat
*/

#include "shell.h"

int	next_range(char *ptr, char tok)
{
  char	*s;

  s = ptr;
  while (*ptr && *ptr != tok)
    ++ptr;
  return (ptr - s);
}

char	*get_range_ascii(char *ascii, char input)
{
  while (strncmp(ascii, &input, next_range(ascii, ',')))
    {
      ascii += next_range(ascii, ':');
      if (!*ascii)
	return (NULL);
      ++ascii;
    }
  return (ascii + next_range(ascii, ',') + 1);
}
