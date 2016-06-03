/*
** auto_complet.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Fri May 27 14:15:52 2016
** Last update Fri Jun  3 16:26:02 2016 Bertrand Buffat
*/

#include "shell.h"

char		is_substr_in_path(t_prompt *prompt, DIR *dir, char flag)
{
  struct dirent	*entry;
  char		*save;

  while ((entry = readdir(dir)))
    if (!strncmp(entry->d_name, prompt->line + prompt->offset,
		 prompt->count_char - prompt->offset) &&
	entry->d_name[0] != '.')
      {
	if (flag
	    && (strncmp(prompt->auto_completion, entry->d_name,
			prompt->size_completion)
		|| (get_n_same_bytes(save, entry->d_name) == prompt->size_completion)))
	  return (-1);
	save = entry->d_name;
	prompt->size_completion = strlen(entry->d_name);
	memcpy(prompt->auto_completion, entry->d_name, prompt->size_completion);
	flag = 1;
      }
  return (flag);
}

void	search_substr_in_path(t_prompt *prompt, char **path, char flag)
{
  DIR	*dir;

  if (!*path)
    {
      if (!flag)
	prompt->size_completion = 0;
      return ;
    }
  if (!(dir = opendir(*path)))
    return (search_substr_in_path(prompt, ++path, flag));
  if ((flag = is_substr_in_path(prompt, dir, flag)) == -1)
    {
      prompt->size_completion = 0;
      closedir(dir);
      return ;
    }
  closedir(dir);
  return (search_substr_in_path(prompt, ++path, flag));
}

void	search_command(t_prompt *prompt, char **env)
{
  char	**path;
  char	*tmp;

  if (!(tmp = get_var_env(env, "PATH=")))
    {
      prompt->size_completion = 0;
      return ;
    }
  path = my_str_to_wordtab_pattern(tmp, ":");
  search_substr_in_path(prompt, path, 0);
  free_tab(path);
}

void	search_file(t_prompt *prompt)
{
  DIR	*dir;
  int	offset_dir;
  char	path[1024];
  int	ret;

  if ((offset_dir =
       get_offset_directory(prompt->line, prompt->count_char)) != -1)
    get_path_from_line(prompt, offset_dir, path);
  else if (!getcwd(path, 1024))
    {
      prompt->size_completion = 0;
      return ;
    }
  if (!(dir = opendir(path)))
    {
      prompt->size_completion = 0;
      return ;
    }
  ret = is_substr_in_path(prompt, dir, 0);
  if (ret == -1 || !ret)
    prompt->size_completion = 0;
  closedir(dir);
}

void	auto_completion(t_shell *sh)
{
  int	ret;

  if ((sh->prompt->offset =
       get_offset(sh->prompt->line, sh->prompt->count_char, &ret)) == -1)
    {
      sh->prompt->size_completion = 0;
      return ;
    }
  if (!ret)
    search_command(sh->prompt, sh->env);
  else
    search_file(sh->prompt);
}
