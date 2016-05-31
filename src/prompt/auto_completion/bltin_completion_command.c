/*
** bltin_completion_command.c for  in /home/buffat_b/couver-shell/src/prompt/auto_completion
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sat May 28 19:12:36 2016
** Last update Tue May 31 13:51:27 2016 Bertrand Buffat
*/

#include "shell.h"

int		count_substr_in_path(t_prompt *prompt, DIR *dir)
{
  struct dirent	*entry;
  int		count;

  count = 0;
  while ((entry = readdir(dir)))
    if (!strncmp(entry->d_name, prompt->line + prompt->offset,
		 prompt->count_char - prompt->offset))
      ++count;
  return (count);
}

int	count_commands(t_prompt *prompt, char **env)
{
  DIR	*dir;
  char	**path;
  char	*tmp;
  int	count;
  int	i;

  if (!(tmp = get_var_env(env, "PATH=")))
    return (0);
  count = 0;
  path = my_str_to_wordtab_pattern(tmp, ":");
  i = -1;
  while (path[++i])
    if ((dir = opendir(path[i])))
      {
	count += count_substr_in_path(prompt, dir);
	closedir(dir);
      }
  free_tab(path);
  return (count);
}

void		print_substr_in_path(t_prompt *prompt, DIR *dir, t_list **list)
{
  struct dirent	*entry;

  while ((entry = readdir(dir)))
    if (!strncmp(entry->d_name, prompt->line + prompt->offset,
		 prompt->count_char - prompt->offset))
      put_in_list(list, entry->d_name);
}

bool    ask_print_commands(int count)
{
  char	buffer[2];

  write(1, "Display all ", 12);
  put_nbr(count);
  write(1, " possibilities? (y or n)", 24);
  buffer[0] = 0;
  while (buffer[0] != 'y')
    {
      if (buffer[0] == 'n')
	return (0);
      read(0, buffer, 1);
    }
  write(1, "\n", 1);
  return (1);
}

void		print_commands(t_prompt *prompt, char **env, int count)
{
  DIR		*dir;
  t_list	*list;
  char		**path;
  char		*tmp;
  int		i;

  if (!(tmp = get_var_env(env, "PATH=")))
    return ;
  if (!(list = malloc(sizeof(*list))))
    return ;
  list = NULL;
  path = my_str_to_wordtab_pattern(tmp, ":");
  i = -1;
  while (path[++i])
    if ((dir = opendir(path[i])))
      {
	print_substr_in_path(prompt, dir, &list);
	closedir(dir);
      }
  clean_screen(prompt);
  print_dat_list(prompt, list, count);
  free_list(&list);
  free_tab(path);
  update_local_prompt(prompt);
}
