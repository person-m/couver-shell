/*
** get_std_input.c for  in /home/buffat_b/couver-shell/src
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sun May 29 04:12:22 2016
** Last update Wed Jun  1 22:16:10 2016 mohamed-laid hedia
*/

#include "shell.h"

char	*one_function_get_line(char *old_line,
			       int turn,
			       int old_size,
			       int counter)
{
  char	buffer[1024];
  char	*line;
  int	new_size;

  if (!(line = malloc(sizeof(char) * (turn * 1024))))
    return (NULL);
  if (old_line)
    {
      memcpy(line, old_line, old_size);
      free(old_line);
    }
  if (!(new_size = read(0, buffer, 1024)) || counter > 128)
    {
      line[old_size] = 0;
      return (line);
    }
  memcpy(line + old_size, buffer, new_size);
  return (one_function_get_line(line, ++turn, new_size + old_size, ++counter));
}

void	get_std_input(t_shell *sh)
{
  char	**cmd;
  char	**instr;
  char	*line;
  int	i;
  int	ret;
  int	ret2;

  if (!(line = one_function_get_line(NULL, 1, 0, 0))
      || !(instr = my_str_to_wordtab_pattern(line, "\n")))
    return ;
  i = -1;
  while (instr[++i])
    {
      cmd = lexer(instr[i], 0);
      ret = replace_vars(&cmd, sh);
      ret2 = replace_exclam_dot(&cmd, sh);
      update_history(instr[i], sh);
      if (ret == 1 && ret2 == 1)
	do_the_thing(sh, &cmd);
    }
  free(line);
  free_tab(instr);
}
