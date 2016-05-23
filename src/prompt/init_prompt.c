/*
** init.c for  in /home/buffat_b/42sh_tmp
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 18 22:21:57 2016
** Last update Mon May 23 20:43:44 2016 
*/

#include "42sh.h"

void	free_prompt(t_prompt *prompt)
{
  free(prompt->start_line_str);
  free(prompt->line);
  free(prompt->space);
  free(prompt);
}

int	get_actual_line(t_prompt *prompt)
{
  char	buffer[16];
  int	i;
  int	res;

  ioctl(0, TCSETS, &prompt->raw_mode);
  write(1, "\033[6n", 4);
  read (0 ,buffer , sizeof(buffer));
  ioctl(0, TCSETS, &prompt->standard_mode);
  i = 0;
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
  prompt->start_line += (strlen(prompt->line) / prompt->nbcols) + 2;
  prompt->start_line_str = str_cat(str_cat(str_dup("\033["),
					   int_to_str(prompt->start_line)),
				   strdup(";1H"));
  write(1, prompt->start_line_str, strlen(prompt->start_line_str));

  //initialize buffer line
  prompt->line[0] = 0;

  //initialize counters
  prompt->count_char = 0;
  prompt->count_pos = 0;
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
  prompt->start_line_str = str_cat(str_cat(str_dup("\033["),
					   int_to_str(prompt->start_line)),
				   strdup(";1H"));

  //get cols and lines
  prompt->nbcols = tigetnum("cols");
  prompt->nblines = tigetnum("lines");

  //malloc buffer line
  if (!(prompt->line = malloc(sizeof(char) * (prompt->nbcols * prompt->nblines))))
    return (NULL);
  prompt->line[0] = 0;

  //malloc erase buffer and fill it with spaces
  if (!(prompt->space = malloc(sizeof(char) * (prompt->nbcols * prompt->nblines))))
    return (NULL);
  memset(prompt->space, ' ', prompt->nbcols * prompt->nblines - 1);

  //initialize counters
  prompt->count_char = 0;
  prompt->count_pos = 0;

  return (prompt);
}
