/*
** annex.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 14:14:58 2016
** Last update Sun May 29 02:56:52 2016 
*/

#include "prompt.h"

int	get_actual_line(t_prompt *prompt)
{
  char	buffer[16];
  int	i;
  int	res;

  if (ioctl(0, TCSETS, &prompt->raw_mode) == -1)
    return (-1);
  if (write(1, "\033[6n", 4) <= 0)
    return (-1);
  buffer[read(0, buffer, 15)] = 0;
  i = 0;
  if (buffer[0] != 27)
    return (get_actual_line(prompt));
  while (buffer[i] != '[')
    ++i;
  res = 0;
  while (buffer[++i] != ';')
    {
      res *= 10;
      res += (buffer[i] - '0');
    }
  return (res);
}

int	size_of_int(int n)
{
  int	i;

  i = 1;
  while (n > 9)
    {
      ++i;
      n /= 10;
    }
  return (i);
}

void	int_to_str_rec(char *s, int range, int nbr)
{
  if (nbr > 9)
    int_to_str_rec(s, range - 1, nbr / 10);
  s[range] = nbr % 10 + '0';
}

void	fill_tab_caps(char *tab, int line, int cols)
{
  int	i;

  i = -1;
  tab[++i] = 27;
  tab[++i] = '[';
  i += size_of_int(line);
  int_to_str_rec(tab, i, line);
  tab[++i] = ';';
  i += size_of_int(cols);
  int_to_str_rec(tab, i, cols);
  tab[++i] = 'H';
  tab[++i] = 0;
}
