/*
** backquote.c for backquote in /Users/couver_v/Epitech/rendu/couver-shell/src/backquote
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Fri May 27 16:42:28 2016 Vincent COUVERCHEL
** Last update Fri May 27 16:42:28 2016 Vincent COUVERCHEL
*/

#include "shell.h"
#include "backquote_utils.c"

#define BUF_SIZE 1024

static int	get_match_quote(char **command, int i)
{
  if (!strcmp(command[i], "`"))
  {
    i++;
    while (command[i] && strcmp(command[i], "`"))
      i++;
  }
  else
    i++;
  return (i);
}

static char	*father_action(int fd[2], int *size)
{
  int		ret;
  char		buf[BUF_SIZE + 1];
  char		*new_line;

  new_line = NULL;
  close(fd[1]);
  while ((ret = read(fd[0], buf, BUF_SIZE)) > 0)
  {
    if (!(new_line = realloc(new_line, *size + ret + 1)))
      return (NULL);
    memcpy(new_line + *size, buf, ret);
    new_line[*size + ret] = 0;
    *size += ret;
  }
  close(fd[0]);
  wait(NULL);
  return (new_line);
}

static void	son_action(int fd[2], t_shell *sh, char ***command)
{
  close(fd[0]);
  dup2(fd[1], 1);
  do_the_thing(sh, command);
  close(fd[1]);
  exit(0);
}

static char	**exec_backquote(char ***command, t_shell *sh)
{
  int		fd[2];
  int		size;
  char		*new_line;
  char		**new_command;
  int		ret_fork;

  size = 0;
  new_line = NULL;
  new_command = NULL;
  pipe(fd);
  if ((ret_fork = fork()) == -1)
    return (NULL);
  else if (ret_fork == 0)
    son_action(fd, sh, command);
  else
    new_line = father_action(fd, &size);
  if (new_line)
    new_command = lexer(new_line);
  free(new_line);
  return (new_command);
}

int	backquote(char ***command, t_shell *sh)
{
  int	i;
  int	j;
  char	**new_command;
  char	**sub_command;

  i = 0;
  while ((*command)[i])
  {
    if (!strcmp((*command)[i], "`"))
    {
      j = get_match_quote(*command, i);
      sub_command = get_sub_tab(*command, i + 1, j - i - 1);
      if ((new_command = exec_backquote(&sub_command, sh)))
	*command = insert_tab_in_tab(*command, new_command, i, j - i + 1);
      free_tab(new_command);
      free_tab(sub_command);
    }
    i++;
  }
  return (0);
}