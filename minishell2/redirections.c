/*
** redirections.c for 42sh in /home/hedia_m/couver-shell/minishell2
** 
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
** 
** Started on  Sun May 22 18:26:56 2016 mohamed-laid hedia
** Last update Mon May 23 22:03:38 2016 mohamed-laid hedia
*/

#include "mo.h"

void	write_on_pipe(int fd, char *file)
{
  char	*str;

  write(1, "? ", 2);
  while ((str = get_next_line(0)) && strcmp(str, file))
    {
      write(fd, str, strlen(str));
      write(fd, "\n", 1);
      free(str);
      printf("%s", "? ");
    }
  close(fd);
}

int	double_left_redirection(char *red, char *file)
{
  int	p[2];

  if (!strcmp(red, "<<"))
    {
      if (pipe(p) == -1)
	{
	  fprintf(stderr, "%s\n", strerror(errno));
          return (-1);
	}
      write_on_pipe(p[1], file);
      if (dup2(p[0], 0) == -1)
	{
	  fprintf(stderr, "%s\n", strerror(errno));
          return (-1);
	}
      close(p[0]);
      return (1);
    }
  return (-1);
}

int	left_redirection(char *red, char *file)
{
  int	fd;

  if (!strcmp(red, "<"))
    {
      if ((fd = open(file, O_RDONLY)) == -1)
        {
          fprintf(stderr, "%s\n", strerror(errno));
          return (-1);
        }
      else
        if (dup2(fd, 0) == -1)
          {
            fprintf(stderr, "%s\n", strerror(errno));
            return (-1);
          }
      close(fd);
      return (1);
    }
  return (double_left_redirection(red, file));
}

int	double_right_redirection(char *red, char *file)
{
  int	fd;

  if (!strcmp(red, ">>"))
    {
      if ((fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 00644)) == -1)
        {
          fprintf(stderr, "%s\n", strerror(errno));
          return (-1);
        }
      else
        if (dup2(fd, 1) == -1)
          {
            fprintf(stderr, "%s\n", strerror(errno));
            return (-1);
          }
      close(fd);
      return (1);
    }
  return (left_redirection(red, file));
}

int	right_redirection(char *red, char *file)
{
  int	fd;

  if (!strcmp(red, ">"))
    {
      if ((fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 00644)) == -1)
	{
	  fprintf(stderr, "%s\n", strerror(errno));
	  return (-1);
	}
      else
	if (dup2(fd, 1) == -1)
	  {
	    fprintf(stderr, "%s\n", strerror(errno));
	    return (-1);
	  }
      close(fd);
      return (1);
    }
  return (double_right_redirection(red, file));
}
