/*
** fill_history.c for fill_history in /home/riamon_v/rendu/PSU/couver-shell/history
**
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
**
** Started on  Sun May 22 10:23:47 2016 vincent riamon
** Last update Fri May 27 14:55:52 2016 Melvin Personnier
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

void		update_history(char **line, t_shell *sh)
{
  int		fd;
  int		i;
  char		*hist;
  int		ret;

  i = tab_len(sh->history);
  ret = create_history_file(&hist, sh);
  sh->history = realloc(sh->history, (sizeof(char *) * (i + 2)));
  if ((sh->history[i] = wortab_in_str(line)) == NULL)
    return ;
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
      while (--i > 0)
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

/* int		main(__attribute__((unused))int argc, char **argv, char **env) */
/* { */
/*   t_shell	sh; */

/*   sh.env = cpy_env(env); */
/*   fill_history(&sh); */
/*   /\* write(1, "$> ", 3); *\/ */
/*   /\* while ((s = get_next_line(0))) *\/ */
/*   /\*   { *\/ */
/*   /\*     write(1, "$> ", 3); *\/ */
/*   /\*     if (s[0] != 0) *\/ */
/*   /\* 	{ *\/ */
/*   update_history(argv + 1, &sh); */
/*     /\* 	  i += 1; *\/ */
/*     /\* 	} *\/ */
/*     /\*   if (!strcmp(s, "history")) *\/ */
/*     /\*     print_tab_fd(tab, 1, 1); *\/ */
/*     /\*   free(s); *\/ */
/*     /\* } *\/ */
/*   free_tab(sh.history); */
/*   free_tab(sh.env); */
/*   execl("/bin/sh", "/bin/sh", "-c", "cat /home/riamon_v/.42_history", NULL); */
/*   return (0); */
/* } */
