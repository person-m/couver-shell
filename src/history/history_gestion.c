/*
** fill_history.c for fill_history in /home/riamon_v/rendu/PSU/couver-shell/history
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Sun May 22 10:23:47 2016 vincent riamon
** Last update Wed May 25 22:21:45 2016 
*/

#include "my.h"
#include "../../include/shell.h"

static char	*wortab_in_str(char **tab)
{
  char		*str;
  int		i;
  int		j;
  int		k;
  int		len;

  i = -1;
  k = 0;
  str = NULL;
  len = 0;
  if (!tab[0])
    return (NULL);
  while (tab[++i])
    {
      j = 0;
      len += strlen(tab[i]) + 1;
      str = realloc(str, sizeof(char) * (len + 1));
      while (tab[i][j])
	str[k++] = tab[i][j++];
      str[k++] = ' ';
    }
  str[k - 1] = 0;
  return (str);
}

void		update_history(char **line, char ***tab, char **env)
{
  int		fd;
  int		i;
  char		*hist;

  i = tab_len(*tab);
  hist = concat_str(get_var_env(env, "HOME="), ".42_history", '/');
  if ((fd = open(hist, O_RDWR | O_APPEND)) == -1)
    return ;
  *tab = realloc(*tab, (sizeof(char *) * (i + 2)));
  if (((*tab)[i] = wortab_in_str(line)) == NULL)
    return ;
  (*tab)[i + 1] = NULL;
  write(fd, (*tab)[i], strlen((*tab)[i]));
  write(fd, "\n", 1);
  close(fd);
  free(hist);
}

char		**fill_history(char **env)
{
  int		fd;
  char		*s;
  char		**tab;
  int		i;
  char		*hist;

  i = 0;
  hist = concat_str(get_var_env(env, "HOME="), ".42_history", '/');
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

int		cmd_history(char **tab, t_shell *sh)
{
  int		i;
  int		fd;
  char		*hist;

  i = -1;
  hist = concat_str(get_var_env(sh->env, "HOME="), ".42_history", '/');
  if (tab_len(tab) == 1)
    while (sh->history[++i])
      printf("   %d  %s\n", i + 1, sh->history[i]);
  else if (!strcmp(tab[1], "-c"))
    {
      i = tab_len(sh->history) + 1;
      while (--i > 0)
	{
	  free(sh->history[i]);
	  sh->history[i] = NULL;
	}
      if ((fd = open(hist, O_RDONLY | O_TRUNC)) == -1)
	return (-1);
    }
  free(hist);
  return (0);
}

/* int		main(__attribute__((unused))int argc, char **argv, char **env) */
/* { */
/*   char		**tab; */
/*   char	*s; */

/*   tab = fill_history(env); */
/*   write(1, "$> ", 3); */
/*   while ((s = get_next_line(0))) */
/*     { */
/*       write(1, "$> ", 3); */
/*       if (s[0] != 0) */
/*   	{ */
/*   update_history(argv + 1, &tab, env); */
/*     	  i += 1; */
/*     	} */
/*       if (!strcmp(s, "history")) */
/*         print_tab_fd(tab, 1, 1); */
/*       free(s); */
/*     } */
/*   free_tab(tab); */
/*   execl("/bin/sh", "/bin/sh", "-c", "cat /$home/.history", NULL); */
/*   return (0); */
/* } */
