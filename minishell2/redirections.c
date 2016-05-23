/*
** redirections.c for 42sh in /home/hedia_m/couver-shell/minishell2
** 
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
** 
** Started on  Sun May 22 18:26:56 2016 mohamed-laid hedia
** Last update Sun May 22 20:00:12 2016 mohamed-laid hedia
*/

#include "mo.h"

void	write_on_pipe(int fd, char *file)
{
  char	*str;

  write(1, "? ", 2);
  while ((str = get_next_line(0)) && my_strcmp(str, file))
    {
      write(fd, str, my_strlen(str));
      write(fd, "\n", 1);
      free(str);
      my_putstr("? ");
    }
  close(fd);
}

int	change_fd4(char *red, char *file)
{
  int	p[2];

  if (!strcmp(red, "<<"))
    {
      if (pipe(p) == -1)
	{
	  fprintf(2, "%s\n", strerror(errno));
          return (-1);
	}
      write(p[1], file);
      if (dup2(p[0], 0) == -1)
	{
	  fprintf(2, "%s\n", strerror(errno));
          return (-1);
	}
      close(p[0]);
      return (1);
    }
  return (-1);
}

int	change_fd3(char *red, char *file)
{
  int	fd;

  if (!strcmp(red, "<"))
    {
      if ((fd = open(file, O_RDONLY)) == -1)
        {
          fprintf(2, "%s\n", strerror(errno));
          return (-1);
        }
      else
        if (dup2(fd, 0) == -1)
          {
            fprintf(2, "%s\n", strerror(errno));
            return (-1);
          }
      close(fd);
      return (1);
    }
  return (change_fd4(red, file));
}

int	change_fd2(char *red, char *file)
{
  int	fd;

  if (!strcmp(red, ">>"))
    {
      if ((fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 00644)) == -1)
        {
          fprintf(2, "%s\n", strerror(errno));
          return (-1);
        }
      else
        if (dup2(fd, 1) == -1)
          {
            fprintf(2, "%s\n", strerror(errno));
            return (-1);
          }
      close(fd);
      return (1);
    }
  return (change_fd3(red, file));
}

int	change_fd(char *red, char *file)
{
  int	fd;

  if (!strcmp(red, ">"))
    {
      if ((fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00644)) == -1)
	{
	  fprintf(2, "%s\n", strerror(errno));
	  return (-1);
	}
      else
	if (dup2(fd, 1) == -1)
	  {
	    fprintf(2, "%s\n", strerror(errno));
	    return (-1);
	  }
      close(fd);
      return (1);
    }
  return (change_fd2(red, file));
}
