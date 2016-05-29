/*
** fct_prompt.c for  in /home/buffat_b/couver-shell/src/prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sun May 29 02:37:42 2016
** Last update Sun May 29 02:55:54 2016 
*/

#include "shell.h"

void	exit_shell(t_shell *sh)
{
  clean_screen(sh->prompt);
  ioctl(0, TCSETS, &sh->prompt->standard_mode);
  write(1, "exit\n", 5);
  free_prompt(sh->prompt);
  free_tab(sh->env);
  free_tab(sh->alias);
  free_tab(sh->history);
  exit(sh->ret);
}

void	check_auto_compet(t_shell *sh)
{
  DIR	*dir;
  char	path[1024];
  int	offset;
  int	ret;

  if (!sh->prompt->size_completion)
    {
      bltin_completion(sh->prompt, sh->env);
      return ;
    }
  memcpy(sh->prompt->line + sh->prompt->count_char,
  sh->prompt->auto_completion + (sh->prompt->count_char - sh->prompt->offset),
  sh->prompt->size_completion - (sh->prompt->count_char - sh->prompt->offset));
  sh->prompt->count_char += sh->prompt->size_completion
  - (sh->prompt->count_char - sh->prompt->offset);
  sh->prompt->count_pos = sh->prompt->count_char;
  offset = get_offset(sh->prompt->line, sh->prompt->count_char, &ret);
  memcpy(path, sh->prompt->line + offset,
  sh->prompt->count_char - offset);
  path[sh->prompt->count_char - offset] = 0;
  if (!(dir = opendir(path)))
    return ;
  sh->prompt->line[sh->prompt->count_char++] = '/';
  ++sh->prompt->count_pos;
}
