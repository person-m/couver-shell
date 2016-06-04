/*
** annex_auto_compet.c for  in /home/buffat_b/couver-shell/src/prompt/auto_completion
** 
** Made by Bertrand Buffat
** Login   <buffat_b@epitech.net>
** 
** Started on  Sat Jun  4 17:10:03 2016 Bertrand Buffat
** Last update Sat Jun  4 17:13:06 2016 Bertrand Buffat
*/

#include "shell.h"

char		is_subcommand_in_path(t_prompt *prompt, DIR *dir, char flag)
{
  struct dirent	*entry;

  while ((entry = readdir(dir)))
    if (!strncmp(entry->d_name, prompt->line + prompt->offset,
                 prompt->count_char - prompt->offset)
        && entry->d_name[0] != '.')
      {
	if (flag
	    && strncmp(prompt->auto_completion, entry->d_name,
		       prompt->size_completion))
	  return (-1);
	prompt->size_completion = strlen(entry->d_name);
	memcpy(prompt->auto_completion, entry->d_name, prompt->size_completion);
	flag = 1;
      }
  return (flag);
}
