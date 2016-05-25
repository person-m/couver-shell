/*
** init_prompt.c for  in /home/buffat_b/couver-shell/src/prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:56:28 2016
** Last update Tue May 24 23:32:39 2016 
*/

#include "shell.h"

void	free_prompt(t_prompt *prompt)
{
  free(prompt->start_line_str);
  free(prompt->line);
  free(prompt->auto_completion);
  free(prompt->final_line);
  free(prompt);
}

int	get_actual_line(t_prompt *prompt)
{
  char	buffer[16];
  int	i;
  int	res;

  while (ioctl(0, TCSETS, &prompt->raw_mode) == -1);
  while (write(1, "\033[6n", 4) <= 0);
  while ((res = read(0 ,buffer , 15)) == 0);
  buffer[res] = 0;
  i = 0;
  if (buffer[0] != 27)
    return (get_actual_line(prompt));
  while (buffer[i] != '[')
    ++i;
  res = 0;
  while (buffer[++i] != ';')
    {
      res *= 10;
      res += (buffer[i] - '0');
    }
  return (res);
}

void	update_prompt(t_prompt *prompt)
{
  //get new line : int and string
  free(prompt->start_line_str);
  prompt->start_line = get_actual_line(prompt);
  ioctl(0, TCSETS, &prompt->non_canon_mode);
  prompt->start_line_str = str_cat(str_cat(str_dup("\033["),
					   int_to_str(prompt->start_line)),
				   strdup(";1H"));

  //initialize counters
  prompt->count_char = 0;
  prompt->count_pos = 0;

  //erase buffer
  memset(prompt->final_line, ' ', prompt->nbcols * prompt->nblines - 1);
}

t_prompt	*init_prompt(void)
{
  t_prompt	*prompt;

  if (!(prompt = malloc(sizeof(*prompt))))
    return (NULL);

  //set termios struct
  ioctl(0, TCGETS, &prompt->standard_mode);
  get_non_canon(prompt);
  get_raw_mode(prompt);

  //get term info
  setupterm(NULL, 1, (int *)0);

  //get start line : int and string
  prompt->start_line = get_actual_line(prompt);
  ioctl(0, TCSETS, &prompt->standard_mode);
  prompt->start_line_str = str_cat(str_cat(str_dup("\033["),
					   int_to_str(prompt->start_line)),
				   strdup(";1H"));

  //get cols and lines
  prompt->nbcols = tigetnum("cols");
  prompt->nblines = tigetnum("lines");

  //init prompt
  prompt->prompt = str_dup("Ceci est un prompt > ");
  prompt->size_prompt = strlen(prompt->prompt);

  //malloc buffer line
  if (!(prompt->line = malloc(sizeof(char) * (prompt->nbcols * prompt->nblines))))
    return (NULL);

  //malloc buffer final_line
  if (!(prompt->final_line = malloc(sizeof(char) * (prompt->nbcols * prompt->nblines))))
    return (NULL);
  //  memset(prompt->final_line, ' ', prompt->nbcols * prompt->nblines - 1);

  //init auto completion
  if (!(prompt->auto_completion = malloc(sizeof(char) * (prompt->nbcols * prompt->nblines))))
    return (NULL);
  memset(prompt->auto_completion, ' ', prompt->nbcols * prompt->nblines - 1);
  prompt->size_completion = strlen("   auto_completion here");
  memcpy(prompt->auto_completion, "   auto_completion here", prompt->size_completion);

  //initialize counters
  prompt->count_char = 0;
  prompt->count_pos = 0;

  return (prompt);
}
