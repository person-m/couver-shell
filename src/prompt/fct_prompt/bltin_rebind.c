/*
** bltin_rebind.c for  in /home/buffat_b/couver-shell/src/prompt/fct_prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sun May 29 20:34:02 2016
** Last update Mon May 30 22:46:54 2016 Bertrand Buffat
*/

#include "shell.h"

bool	is_alpha(char *s)
{
  while (*s)
    {
      if ((*s < 'A' || *s > 'z')
	  || (*s > 'Z' && *s < 'a'))
	return (0);
      ++s;
    }
  return (1);
}

bool	rebind_format(char **cmd)
{
  if ((!cmd[1] || !cmd[2])
      && write(2, "Rebind command needs two valid arguments\n", 41))
    return (0);
  else if (cmd[1][1]
	   && write(2, "Rebind requires char type as first argument\n", 44))
    return (0);
  else if ((!is_alpha(cmd[1]) || !is_alpha(cmd[2]))
	   && write(2, "Rebind only works for alphabetical characters\n", 46))
    return (0);
  return (1);
}

void		rebind(char **cmd, t_shell *sh)
{
  t_caps	*caps;
  char		*str;
  char		*ptr;
  int		size;
  int		size2;
  int		range;

  caps = sh->prompt->caps;
  if (!rebind_format(cmd)
      || !(ptr = get_range_ascii(caps->ascii, cmd[1][0])))
    return ;
  size = strlen(caps->ascii);
  size2 = strlen(cmd[2]);
  range = ptr - caps->ascii;
  if (!(str =
	malloc(sizeof(char) * (size + size2 + 1))))
    return ;
  memcpy(str, caps->ascii, range);
  memcpy(str + range, cmd[2], size2);
  while (*ptr && *ptr != ':')
    ++ptr;
  memcpy(str + range + size2, ptr, strlen(ptr));
  str[size + size2] = 0;
  free(caps->ascii);
  caps->ascii = str;
}
