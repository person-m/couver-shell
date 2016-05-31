/*
** bltin_completion.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sat May 28 18:58:33 2016
** Last update Tue May 31 13:50:16 2016 Bertrand Buffat
*/

#include "shell.h"

void		print_substr_in_directory(t_prompt *prompt, DIR *dir)
{
  struct dirent	*entry;

  clean_screen(prompt);
  while ((entry = readdir(dir)))
    {
      if (!strncmp(entry->d_name, prompt->line + prompt->offset,
		   prompt->count_char - prompt->offset)
	  && entry->d_name[0] != '.')
	{
	  write(1, entry->d_name, strlen(entry->d_name));
	  write(1, "\n", 1);
	}
    }
  update_local_prompt(prompt);
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
  print_substr_in_directory(prompt, dir);
  closedir(dir);
}

void	 bltin_completion(t_prompt *prompt, char **env)
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
