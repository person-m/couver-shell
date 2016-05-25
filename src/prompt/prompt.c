/*
** prompt.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 13:17:48 2016
** Last update Wed May 25 15:17:12 2016 
*/

#include "shell.h"

char	get_input(t_prompt *prompt)
{
  char	buffer[1024];

  //read standard input
  buffer[read(1, buffer, 1024)] = 0;

  //if nothing
  if (!buffer[0])
    return (0);

  //if just one character
  else if (!buffer[1])
    return (buffer[0]);

  //if complex string
  move_cursor(prompt, buffer);

  return (0);
}

void	which_input(t_prompt *prompt, char input)
{

  //if delete character
  if (input == 127)
    delete_char(prompt);

  //if return line
  else if (input == '\n')
    return ;

  //if normal character
  else
    add_char(prompt, input);

}

void	loop_prompt(t_prompt *prompt)
{
  char	input;

  input = 0;
  aff_prompt(prompt);
  while ((input = get_input(prompt)) != '\n')
    {
      if (input)
	{
	  which_input(prompt, input);
	  aff_prompt(prompt);
	}
    }
  clean_screen(prompt);
  prompt->line[prompt->count_char] = 0;
}
