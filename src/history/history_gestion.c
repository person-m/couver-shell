/*
** fill_history.c for fill_history in /home/riamon_v/rendu/PSU/couver-shell/history
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Sun May 22 10:23:47 2016 vincent riamon
** Last update Tue May 31 17:00:17 2016 vincent riamon
*/

#include "my.h"
#include "../../include/shell.h"

static int	create_history_file(char **hist, t_shell *sh)
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

char	*wordtab_in_str(char **tab, int mode)
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
      if (mode == 1)
	free(tab[i]);
    }
  str[k - 1] = 0;
  return (str);
}

int	        is_empty_line(char *str)
{
  int		i;

  i = 0;
  if (str[0] == 0)
    return (1);
  while (str[i])
    {
      if (str[i] == ' ' || str[i] == '\t')
	i = i + 1;
      else
	return (0);
    }
  return (1);
}

void		update_history(char *line, t_shell *sh)
{
  int		fd;
  int		i;
  char		*hist;
  int		ret;

  i = tab_len(sh->history);
  ret = create_history_file(&hist, sh);
  if (is_empty_line(line))
    return ;
  sh->history = realloc(sh->history, (sizeof(char *) * (i + 2)));
  sh->history[i] = strdup(line);
  sh->history[i + 1] = NULL;
  sh->size_hist += 1;
  if (ret == -1 || (fd = open(hist, O_RDWR | O_APPEND)) == -1)
    return ;
  write(fd, sh->history[i], strlen(sh->history[i]));
  write(fd, "\n", 1);
  close(fd);
  free(hist);
}

void		fill_history(t_shell *sh)
{
  int		fd;
  char		*s;
  int		i;
  char		*hist;
  int		ret;

  i = 0;
  sh->history = my_malloc(sizeof(char *) * 1);
  sh->history[0] = NULL;
  ret = create_history_file(&hist, sh);
  if (ret == -1 || (fd = open(hist, O_CREAT | O_RDONLY, 0644)) == -1)
    return ;
  while ((s = get_next_line(fd)))
    {
      sh->history = realloc(sh->history, sizeof(char *) * (i + 2));
      sh->history[i] = strdup(s);
      sh->history[i + 1] = NULL;
      free(s);
      i++;
    }
  sh->history[tab_len(sh->history)] = NULL;
  sh->size_hist = tab_len(sh->history);
  close(fd);
  free(hist);
}

int		cmd_history(char **tab, t_shell *sh)
{
  int		i;
  int		fd;
  char		*hist;
  int		ret;

  i = -1;
  ret = create_history_file(&hist, sh);
  if (tab_len(tab) == 1)
    while (sh->history[++i])
      printf("   %d  %s\n", i + 1, sh->history[i]);
  else if (!strcmp(tab[1], "-c"))
    {
      i = tab_len(sh->history) + 1;
      sh->size_hist = 0;
      while (--i >= 0)
	{
	  free(sh->history[i]);
	  sh->history[i] = NULL;
	}
      if (ret == -1 || (fd = open(hist, O_RDONLY | O_TRUNC)) == -1)
	return (-1);
    }
  if (ret == 0)
    free(hist);
  return (0);
}
