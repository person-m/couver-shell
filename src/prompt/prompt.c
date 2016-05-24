/*
** prompt.c for  in /home/buffat_b/42sh_tmp
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Mon May 23 19:11:45 2016
<<<<<<< HEAD
** Last update Mon May 23 22:33:36 2016 
=======
** Last update Tue May 24 00:13:53 2016 
>>>>>>> buffat_b
*/

#include "shell.h"

void	erase_screen(t_prompt *prompt)
{
  int	size;

  //get to the start
  write(1, prompt->start_line_str, strlen(prompt->start_line_str));

  size = prompt->size_prompt;
  size += prompt->count_char;
  size += prompt->size_completion;

  write(1, prompt->space, size);

  //get to the start
  write(1, prompt->start_line_str, strlen(prompt->start_line_str));
}

void	aff_prompt(t_prompt *prompt)
{

  erase_screen(prompt);

  //aff prompt
  write(1, "Ceci est un prompt > ", 21);

  //write buffer
  write(1, prompt->line, strlen(prompt->line));

  //auto complete
  write(1, "\033[s", 3);
  write(1, prompt->auto_completion, prompt->size_completion);
  write(1, "\033[u", 3);

  //get cursor back to its place
  move_cursor_back(prompt);
}

char	get_input(t_prompt *prompt)
{
  char	buffer[1024];

  //read standard input
  buffer[read(1, buffer, 1024)] = 0;

  // if nothing
  if (buffer[0] == 0)
    return (0);

  //if just one character
  else if (buffer[1] == 0)
    return (buffer[0]);

  // if complex string
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
  while (input != '\n')
    {
      if ((input = get_input(prompt)))
	{
	  which_input(prompt, input);
	  aff_prompt(prompt);
	}
    }
}
