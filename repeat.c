/*
** repeat.c for  in /home/buffat_b/couver-shell
** 
** Made by Bertrand Buffat
** Login   <buffat_b@epitech.net>
** 
** Started on  Fri Jun  3 21:38:27 2016 Bertrand Buffat
** Last update Fri Jun  3 23:24:49 2016 Bertrand Buffat
*/

#include "shell.h"

bool	is_num(char *s)
{
  while (*s)
    {
      if (*s < '0' || *s > '9')
	return (0);
      ++s;
    }
  return (1);
}

int	get_nbr(char *s, int res)
{
  if (!*s)
    return (res);
  res *= 10;
  res += (*s - '0');
  return (get_nbr(++s, res));
}

void	erase_first_line_tab(char **tab)
{
  char	*tmp;
  int	i;

  tmp = tab[0];
  i = 0;
  while (tab[i])
    {
      tab[i] = tab[i + 1];
      ++i;
    }
  free(tmp);
}

void	loop_repeat(t_shell *sh, char **cmd, int turn)
{
  char	*line;
  int	ret;
  int	ret2;

  line = wordtab_in_str(cmd, 0);
  while (--turn >= 0)
    {
      ret2 = replace_exclam_dot(&cmd, sh);
      ret = replace_vars(&cmd, sh);
      update_history(line, sh);
      if (ret == 1 && ret2 == 1)
	do_the_thing(sh, &cmd);
    }
}

int	repeat(char **cmd, t_shell *sh)
{
  char	*tmp;
  int	turn;

  if ((!cmd[1] || !cmd[2])
      && write(2, "repeat: Too few arguments.\n", 27))
    return (0);
  tmp = cmd[1];
  if (tmp[0] == '"')
    ++tmp;
  if (tmp[strlen(tmp) - 1] == '"')
    tmp[strlen(tmp) - 1] = 0;
  if ((!is_num(tmp))
      && write(2, "repeat: Badly formed number.\n", 29))
    return (0);
  turn = get_nbr(tmp, 0);
  erase_first_line_tab(cmd);
  erase_first_line_tab(cmd);
  loop_repeat(sh, cmd, turn);
  return (1);
}
