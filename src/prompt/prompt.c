/*
** prompt.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 13:17:48 2016
** Last update Wed May 25 00:06:08 2016 
*/

#include "shell.h"

void	erase_down_lines(int nb_lines)
{
  write(1, "\033[K", 3);
  while (--nb_lines >= 0)
    {
      write(1, "\033[B", 3);
      write(1, "\033[K", 3);
    }
}

void	aff_prompt(t_prompt *prompt)
{
  int	nb_lines_buffer;

  //put prompt
  memcpy(prompt->final_line, prompt->prompt, prompt->size_prompt);

  //put line
  memcpy(prompt->final_line + prompt->size_prompt, prompt->line, prompt->count_char);

  //put auto_completion
  memcpy(prompt->final_line + prompt->size_prompt + prompt->count_char,
	 prompt->auto_completion, prompt->size_completion);

  //line's buffer size
  nb_lines_buffer = (prompt->size_prompt + prompt->count_char + prompt->size_completion)
    / prompt->nbcols;

  //if moving out of the screen
  if (prompt->start_line + nb_lines_buffer > prompt->nblines)
    {
      free(prompt->start_line_str);
      --prompt->start_line;
      prompt->start_line_str = str_cat(str_cat(str_dup("\033["),
					       int_to_str(prompt->start_line)),
				       strdup(";1H"));

      //scroll up
      write(1, "\n", 1);
    }

  //get to the start
  write(1, prompt->start_line_str, strlen(prompt->start_line_str));

  //clear previous characters
  erase_down_lines(nb_lines_buffer);

  //get to the start
  write(1, prompt->start_line_str, strlen(prompt->start_line_str));

  //aff total buffer
  write(1, prompt->final_line, prompt->size_prompt + prompt->count_char + prompt->size_completion);

  //get to the start
  write(1, prompt->start_line_str, strlen(prompt->start_line_str));

  //move cursor to its place
  move_cursor_back(prompt);
}

void	clean_screen(t_prompt *prompt)
{
  int	nb_lines_buffer;

  //line's buffer size
  nb_lines_buffer = (prompt->size_prompt + prompt->count_char + prompt->size_completion)
    / prompt->nbcols;

  //get to the start
  write(1, prompt->start_line_str, strlen(prompt->start_line_str));

  //clear previous characters
  erase_down_lines(nb_lines_buffer);

  //get to the start
  write(1, prompt->start_line_str, strlen(prompt->start_line_str));

  //put prompt
  memcpy(prompt->final_line, prompt->prompt, prompt->size_prompt);

  //put line
  memcpy(prompt->final_line + prompt->size_prompt, prompt->line, prompt->count_char);

  //aff buffer
  write(1, prompt->final_line, prompt->size_prompt + prompt->count_char);

  //ready for std output
  write(1, "\n", 1);
}

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
}
