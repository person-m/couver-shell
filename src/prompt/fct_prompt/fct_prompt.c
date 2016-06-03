/*
** fct_prompt.c for  in /home/buffat_b/couver-shell/src/prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sun May 29 02:37:42 2016
** Last update Fri Jun  3 15:38:07 2016 Bertrand Buffat
*/

#include "shell.h"

void	exit_shell(t_shell *sh)
{
  tcsetattr(0, 0, &sh->prompt->standard_mode);
  write(1, "^D\nexit\n", 8);
  free_prompt(sh->prompt);
  free_tab(sh->env);
  free_tab(sh->alias);
  free_tab(sh->history);
  exit(sh->ret);
}

char	*stradd(char *str, char *add)
{
  char	*ptr;
  int	size;
  int	size2;

  size = strlen(str);
  size2 = strlen(add);
  if (!(ptr = malloc(sizeof(char) * size + size2 + 1)))
    return (NULL);
  memcpy(ptr, str, size);
  memcpy(ptr + size, add, size2);
  ptr[size + size2] = 0;
  free(str);
  return (ptr);
}

int	dlen(char **s)
{
  int	i;

  i = -1;
  while (s[++i]);
  return (i);
}

void	get_pwd_prompt(t_prompt *prompt)
{
  char	*term;
  char	*home;

  if (!(term = get_var_env(prompt->env, "PWD=")))
    {
      prompt->size_pwd = 0;
      prompt->pwd = NULL;
      return ;
    }
  prompt->size_pwd = strlen(term);
  memcpy(prompt->pwd, term, prompt->size_pwd);
  if (!(home = get_var_env(prompt->env, "HOME=")))
    return ;
  if (!strncmp(term, home, strlen(home)))
    {
      term += strlen(home);
      memcpy(prompt->pwd + 1, term, strlen(term));
      prompt->pwd[0] = '~';
      prompt->size_pwd = strlen(term) + 1;
    }
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
