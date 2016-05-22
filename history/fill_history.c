/*
** fill_history.c for fill_history in /home/riamon_v/rendu/PSU/couver-shell/history
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Sun May 22 10:23:47 2016 vincent riamon
** Last update Sun May 22 15:23:58 2016 vincent riamon
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

void		print_history(char **tab)
{
  int		i;

  i = -1;
  while (tab[++i])
    {
      write(1, "   ", 3);
      my_putnbr(i + 1);
      write(1, "  ", 2);
      write(1, tab[i], strlen(tab[i]));
      write(1, "\n", 1);
    }
}

char		**fill_history(char **env)
{
  int		fd;
  char		*s;
  char		**tab;
  int		i;
  char		*hist;

  i = 0;
  hist = concat_str(get_var_env(env, "HOME="), ".history", '/');
  if ((fd = open(hist, O_CREAT | O_RDONLY, 0644)) == -1)
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
  free(hist);
  return (tab);
}

void		update_history(char *line, char ***tab, char **env)
{
  int		fd;
  int		i;
  char		*hist;

  i = tab_len(*tab);
  hist = concat_str(get_var_env(env, "HOME="), ".history", '/');
  if ((fd = open(hist, O_RDWR | O_APPEND)) == -1)
    return ;
   *tab = realloc(*tab, (sizeof(char *) * (i + 2)));
  (*tab)[i] = strdup(line);
  (*tab)[i + 1] = NULL;
  write(fd, (*tab)[i], strlen((*tab)[i]));
  write(fd, "\n", 1);
  close(fd);
  free(hist);
}

int		main(__attribute__((unused))int argc, char **argv, char **env)
{
  char		**tab;

  tab = fill_history(env);
  /* write(1, "$> ", 3); */
  /* while ((s = get_next_line(0))) */
  /*   { */
  /*     write(1, "$> ", 3); */
  /*     if (s[0] != 0) */
  /* 	{ */
  update_history(argv[1], &tab, env);
    /* 	  i += 1; */
    /* 	} */
    /*   if (!strcmp(s, "history")) */
    /*     print_tab_fd(tab, 1, 1); */
    /*   free(s); */
    /* } */
  free_tab(tab);
  execl("/bin/sh", "/bin/sh", "-c", "cat /home/riamon_v/.history", NULL);
  return (0);
}
