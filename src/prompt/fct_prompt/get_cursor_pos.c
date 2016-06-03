/*
** annex.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 14:14:58 2016
** Last update Fri Jun  3 22:27:01 2016 Bertrand Buffat
*/

#include "prompt.h"

void	get_actual_line(t_prompt *prompt)
{
  char	buffer[16];
  int	ret;
  int	i;
  
  if (tcsetattr(0, 0, &prompt->raw_mode))
    return (get_actual_line(prompt));  
  if (write(1, "\033[6n", 4) <= 0)
    return ;
  if (!(ret = read(0, buffer, 15)))
    return (get_actual_line(prompt));  
  buffer[ret] = 0;
  if (buffer[0] != 27)
    return (get_actual_line(prompt));
  i = 0;
  while (buffer[i] != '[')
    ++i;
  prompt->start_line = 0;
  while (buffer[++i] != ';')
    {
      prompt->start_line *= 10;
      prompt->start_line += (buffer[i] - '0');
    }
  prompt->start_col = 0;
  while (buffer[++i] != 'R')
    {
      prompt->start_col *= 10;
      prompt->start_col += (buffer[i] - '0');
    }
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
