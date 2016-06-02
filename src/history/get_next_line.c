/*
** get_next_line.c for get_next_line in /home/riamon_v/rendu/CPE/CPE_2015_getnextline
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Wed Jan  6 08:50:21 2016 vincent riamon
** Last update Thu Jun  2 15:33:27 2016 vincent riamon
*/

#include "my.h"

int	create_history_file(char **hist, t_shell *sh)
{
  if (get_var_env(sh->env, "HOME=") != NULL)
    *hist = concat_str(get_var_env(sh->env, "HOME="),
		       ".42_history", '/');
  else
    {
      *hist = NULL;
      return (-1);
    }
  return (0);
}

int		lenstr(char *str, char c)
{
  int           i;

  i = 0;
  while (str[++i] != c);
  return (i);
}

char		*my_realloc(char *str, int nbr_alloc)
{
  int           i;
  char          *tmp;

  i = 0;
  if ((tmp = malloc(sizeof(char) * (lenstr(str, '\0') + nbr_alloc)))
      == NULL)
    return (NULL);
  while (str[i])
    {
      tmp[i] = str[i];
      i = i + 1;
    }
  free(str);
  return (tmp);
}

char		*gnl2(int *i, char **my_line, int *lect, int mod)
{
  if (mod == 0)
    {
      if (*i == 0)
	{
	  if ((*my_line = malloc(sizeof(char) * READ_SIZE + 1)) == NULL)
	    return (NULL);
	}
      else if ((*my_line = my_realloc(*my_line, sizeof(char) * READ_SIZE + 1))
	       == NULL)
	return (NULL);
    }
  else if (mod == 1)
    {
      *i = 0;
      *lect = *lect - 1;
    }
  return (*my_line);
}

char		*get_next_line(const int fd)
{
  static char   *my_line = NULL;
  static char   buff[READ_SIZE + 1];
  static int    lect = 0;
  static int	is_0 = 1;
  static int    i = 0;

  if (!(buff[lenstr(buff, '\0') - lect]))
    {
      if ((lect = read(fd, buff, READ_SIZE)) <= 0)
	return ((buff[lenstr(buff, '\0') - lect - 1] != 10 && is_0--) ?
		my_line : NULL);
      buff[lect] = '\0';
    }
  if (gnl2(&i, &my_line, &lect, 0) == NULL)
    return (NULL);
  while (buff[lenstr(buff, 0) - lect] && buff[lenstr(buff, 0) - lect] != 10)
    my_line[i++] = buff[lenstr(buff, '\0') - lect--];
  my_line[i] = '\0';
  if (buff[lenstr(buff, '\0') - lect] == 10)
    {
      gnl2(&i, &my_line, &lect, 1);
      return (my_line);
    }
  return (get_next_line(fd));
}
