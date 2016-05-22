/*
** fill_history.c for fill_history in /home/riamon_v/rendu/PSU/couver-shell/history
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Sun May 22 10:23:47 2016 vincent riamon
** Last update Sun May 22 13:42:14 2016 vincent riamon
*/

#include "my.h"

void		my_putnbr(int nb)
{
  char		c;

  if (nb > 9)
    my_putnbr(nb / 10);
  c = nb % 10 + 48;
  write(1, &c, 1);
}

void		print_tab_fd(char **tab, int fd, int mode)
{
  int		i;

  i = -1;
  if (mode == 1)
    write(1, "\n", 1);
  while (tab[++i])
    {
      if (mode == 1)
	{
	  write(1, "   ", 3);
	  my_putnbr(i + 1);
	  write(1, "\t", 1);
	}
      write(fd, tab[i], strlen(tab[i]));
      write(fd, "\n", 1);
    }
  if (mode == 1)
    write(1, "$> ", 3);
}

char		**fill_history()
{
  int		fd;
  char		*s;
  char		**tab;
  int		i;

  i = 0;
  if ((fd = open("../.history", O_RDONLY)) == -1)
    return (NULL);
  tab = my_malloc(sizeof(char *) * 1);
  tab[0] = NULL;
  while ((s = get_next_line(fd)))
    {
      tab = realloc(tab, sizeof(char *) * (i + 2));
      tab[i] = strdup(s);
      tab[i + 1] = NULL;
      free(s);
      i++;
    }
  tab[tab_len(tab)] = NULL;
  close(fd);
  return (tab);
}

void		update_history(char *line, char ***tab)
{
  int		fd;
  int		i;

  i = tab_len(*tab);
  if ((fd = open("../.history", O_RDWR)) == -1)
    return ;
   *tab = realloc(*tab, (sizeof(char *) * (i + 2)));
  (*tab)[i] = strdup(line);
  (*tab)[i + 1] = NULL;
  print_tab_fd(*tab, fd, 0);
  close(fd);
}

int		main(__attribute__((unused))int argc, char **argv)
{
  char		**tab;

  tab = fill_history();
  /* write(1, "$> ", 3); */
  /* while ((s = get_next_line(0))) */
  /*   { */
  /*     write(1, "$> ", 3); */
  /*     if (s[0] != 0) */
  /* 	{ */
  update_history(argv[1], &tab);
    /* 	  i += 1; */
    /* 	} */
    /*   if (!strcmp(s, "history")) */
    /*     print_tab_fd(tab, 1, 1); */
    /*   free(s); */
    /* } */
  free_tab(tab);
  execl("/bin/sh", "/bin/sh", "-c", "cat ../.history", NULL);
  return (0);
}
