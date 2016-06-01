/*
** bltin_completion.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sat May 28 18:58:33 2016
** Last update Wed Jun  1 22:45:07 2016 Bertrand Buffat
*/

#include "shell.h"

bool		print_substr_in_directory(t_prompt *prompt, DIR *dir)
{
  struct dirent	*entry;
  char		flag;

  clean_screen(prompt);
  flag = 0;
  while ((entry = readdir(dir)))
    {
      if ((!prompt->count_char
	   || !strncmp(entry->d_name, prompt->line + prompt->offset,
		       prompt->count_char - prompt->offset))
	  && entry->d_name[0] != '.')
	{
	  write(1, entry->d_name, strlen(entry->d_name));
	  write(1, "\n", 1);
	  flag = 1;
	}
    }
  update_local_prompt(prompt);
  return (flag);
}

int		get_substr_tab(t_prompt *prompt, DIR *dir, char **save)
{
  struct dirent	*entry;
  int		min;
  int		ret;

  min = 0;
  ret = 0;
  while ((entry = readdir(dir)))
    {
      if ((!prompt->count_char
	   || !strncmp(entry->d_name, prompt->line + prompt->offset,
		       prompt->count_char - prompt->offset))
	  && entry->d_name[0] != '.')
	{
	  if (!*save && (min = strlen(entry->d_name)))
	    *save = entry->d_name;
	  else if ((ret = get_n_same_bytes(*save, entry->d_name)) == 0)
	    return (0);
	  else if (ret < min)
	    min = ret;
	}
    }
  return (min);
}

void	get_exact_substr(t_prompt *prompt, char *path, int offset_dir)
{
  DIR	*dir;
  char	*save;
  int	ret;

  save = NULL;
  if (!(dir = opendir(path)))
    return ;
  ret = get_substr_tab(prompt, dir, &save);
  if (offset_dir == -1)
    offset_dir = prompt->offset;  
  memcpy(prompt->line + offset_dir, save, ret);
  prompt->count_char = offset_dir + ret;
  prompt->count_pos = prompt->count_char;
  closedir(dir);
}

void	print_files(t_prompt *prompt)
{
  DIR	*dir;
  char	path[1024];
  int	offset_dir;

  if ((offset_dir =
       get_offset_directory(prompt->line, prompt->count_char)) != -1)
    get_path_from_line(prompt, offset_dir, path);
  else if (!getcwd(path, 1024))
    return ;
  if (!(dir = opendir(path)))
    return ;
  if (print_substr_in_directory(prompt, dir))
    get_exact_substr(prompt, path, offset_dir);
  closedir(dir);
}

void	bltin_completion(t_prompt *prompt, char **env)
{
  int	count;
  int	ret;

  if ((prompt->offset =
       get_offset(prompt->line, prompt->count_char, &ret)) == -1)
    return ;
  if (ret == 0
      && (count = count_commands(prompt, env)))
    print_commands(prompt, env, count);
  else
    print_files(prompt);
}
