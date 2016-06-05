/*
** repeat.c for  in /home/buffat_b/couver-shell
**
** Made by Bertrand Buffat
** Login   <buffat_b@epitech.net>
**
** Started on  Fri Jun  3 21:38:27 2016 Bertrand Buffat
** Last update Sat Jun  4 19:31:59 2016 Bertrand Buffat
*/

#include "shell.h"

static bool	is_num(char *s)
{
  int		i;

  i = 0;
  while (s[i])
    {
      if ((s[i] < '0' || s[i] > '9') && (s[i] != '-' || i != 0))
	return (0);
      ++i;
    }
  return (1);
}

static int	get_nbr(char *str)
{
  int		i;
  int		nb;
  unsigned int	tmp;
  
  i = 0;
  nb = 0;
  while (str[i] && str[i] >= '0' && str[i] <= '9')
    i++;
  if (i < 10 || (i < 11 && *str < '3'))
  {
    i = 0;
    while (str[i] && str[i] >= '0' && str[i] <= '9')
    {
      tmp = nb * 10 + (str[i] - '0');
      if (tmp > 0x7fffffff)
	return (0);
      else
	nb = tmp;
      i++;
    }
    return (nb);
  }
  return (0);
}

static void	erase_first_line_tab(char **tab)
{
  int		i;

  i = 0;
  while (tab[i])
    {
      tab[i] = tab[i + 1];
      ++i;
    }
}

int		repeat(char **cmd, t_shell *sh)
{
  char		*tmp;
  int		turn;

  if ((!cmd[1] || !cmd[2])
      && write(2, "repeat: Too few arguments.\n", 27))
    return (-1);
  tmp = cmd[1];
  if (tmp[0] == '"')
    ++tmp;
  if (tmp[strlen(tmp) - 1] == '"')
    tmp[strlen(tmp) - 1] = 0;
  if ((!is_num(tmp))
      && write(2, "repeat: Badly formed number.\n", 29))
    return (-1);
  turn = get_nbr(tmp);
  erase_first_line_tab(cmd);
  erase_first_line_tab(cmd);
  while (--turn >= 0)
    do_the_thing(sh, &cmd, 1);
  return (-sh->ret);
}
