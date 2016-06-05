/*
** src/backquote/backquote_misc.c for src/backquote/backquote_misc in /Users/couver_v/Epitech/rendu/couver-shell
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Thu Jun  2 19:22:38 2016 Vincent COUVERCHEL
** Last update Sun Jun  5 07:11:56 2016 Melvin Personnier
*/

static char	*exec_in_q(char ***command, t_shell *sh)
{
  int		fd[2];
  int		size;
  char		*new_line;
  int		ret_fork;

  size = 0;
  new_line = NULL;
  pipe(fd);
  if ((ret_fork = fork()) == -1)
    return (NULL);
  else if (ret_fork == 0)
    son_action(fd, sh, command);
  else
    new_line = father_action(fd, &size);
  return (new_line);
}

static	void	wordtabncpy(char **dest, char **src, int n)
{
  int		i;

  i = 0;
  while (i < n && src[i])
  {
    dest[i] = my_strdup(src[i]);
    i++;
  }
  dest[i] = NULL;
}
