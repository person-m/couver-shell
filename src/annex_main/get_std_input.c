/*
** get_std_input.c for  in /home/buffat_b/couver-shell/src
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sun May 29 04:12:22 2016
** Last update Tue May 31 17:32:45 2016 vincent riamon
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
      ret2 = replace_exclam_dot(&cmd, sh);
      ret = replace_var_env(&cmd, sh);
      update_history(instr[i], sh);
      if ((ret == 1 && ret2 == 1) && !check_command(cmd))
	the_execution(cmd, sh);
    }
  free(line);
  free_tab(instr);
}
