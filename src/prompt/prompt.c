/*
** prompt.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 13:17:48 2016
** Last update Thu May 26 15:58:18 2016 
*/

#include "shell.h"

char	get_input(t_prompt *prompt)
{
  char	buffer[1024];
  int	ret;

  //read standard input
  ret = read(1, buffer, 1024);
  buffer[ret] = 0;

  //if nothing
  if (!ret)
    return (0);

  //if just one character
  else if (!buffer[1])
    return (buffer[0]);

  //if complex string
  move_cursor(prompt, buffer);

  return (0);
}

void	exit_shell(t_shell *sh, int nbr)
{
  ioctl(0, TCSETS, &sh->prompt->standard_mode);
  write(1, "\nsalut à plus\n", 15);
  free_prompt(sh->prompt);
  free_tab(sh->env);
  free_tab(sh->alias);
  free_tab(sh->history);
  exit(nbr);
}

void	which_input(t_shell *sh, char input)
{

  //if delete character
  if (input == 127)
    delete_char(sh->prompt);

  //if EOF
  else if (input == 4)
    exit_shell(sh, sh->ret);

  //if clear
  else if (input == 12)
    {
      //clear shell
      write(1, "\033[2J" , 4);
      fill_tab_caps(sh->prompt->start_line_str, 0, 0);
      write(1, sh->prompt->start_line_str, strlen(sh->prompt->start_line_str));
      sh->prompt->start_line = get_actual_line(sh->prompt);
      ioctl(0, TCSETS, &sh->prompt->non_canon_mode);
      fill_tab_caps(sh->prompt->start_line_str, sh->prompt->start_line, 1);
    }

  //if return line
  else if (input == '\n')
    return ;

  //nothing
  else if (!input)
    return ;

  //if normal character
  else
    add_char(sh->prompt, input);

}

void	auto_completion(void)
{

}

void	loop_prompt(t_shell *sh)
{
  char	input;

  ioctl(0, TCSETS, &sh->prompt->non_canon_mode);
  input = 0;
  aff_prompt(sh->prompt);
  while ((input = get_input(sh->prompt)) != '\n')
    {
      check_signals(sh);
      which_input(sh, input);
      auto_completion();
      aff_prompt(sh->prompt);
    }
  clean_screen(sh->prompt);
  sh->prompt->line[sh->prompt->count_char] = 0;
  ioctl(0, TCSETS, &sh->prompt->standard_mode);
}
