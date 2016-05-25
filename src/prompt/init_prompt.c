/*
** init_prompt.c for  in /home/buffat_b/couver-shell/src/prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:56:28 2016
** Last update Wed May 25 22:26:39 2016 
*/

#include "shell.h"

bool	fill_caps(char *new, char *old)
{
  int	i;

  if (!old)
    return (0);
  i = 0;
  while (i < 4)
    {
      if (old[i] == 'O')
	new[i] = '[';
      else
	new[i] = old[i];
      ++i;
    }
  new[i] = 0;
  return (1);
}

t_caps		*init_caps(void)
{
  t_caps	*caps;

  if (!(caps = malloc(sizeof(*caps))))
    return (NULL);
  if (!fill_caps(caps->up, tigetstr("kcuu1")))
    return (NULL);
  if (!fill_caps(caps->down, tigetstr("kcud1")))
    return (NULL);
  if (!fill_caps(caps->left, tigetstr("kcub1")))
    return (NULL);
  if (!fill_caps(caps->right, tigetstr("kcuf1")))
    return (NULL);
  return (caps);
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
  if (setupterm(NULL, 1, (int *)0))
    return (NULL);

  //get termcaps
  if (!(prompt->caps = init_caps()))
    return (NULL);

  //get start line : int and string
  prompt->start_line = get_actual_line(prompt);
  ioctl(0, TCSETS, &prompt->standard_mode);
  fill_tab_caps(prompt->start_line_str, prompt->start_line, 1);

  //get cols and lines
  prompt->nbcols = tigetnum("cols");
  prompt->nblines = tigetnum("lines");

  //init prompt
  if (!(prompt->prompt = malloc(sizeof(char) * (prompt->nbcols * prompt->nblines))))
    return (NULL);
  prompt->size_prompt = strlen("Ceci est un prompt > ");
  memcpy(prompt->prompt, "Ceci est un prompt > ", prompt->size_prompt);

  //malloc buffer line
  if (!(prompt->line = malloc(sizeof(char) * (prompt->nbcols * prompt->nblines))))
    return (NULL);

  //malloc buffer final_line
  if (!(prompt->final_line = malloc(sizeof(char) * (prompt->nbcols * prompt->nblines))))
    return (NULL);

  //init auto completion
  if (!(prompt->auto_completion = malloc(sizeof(char) * (prompt->nbcols * prompt->nblines))))
    return (NULL);
  prompt->size_completion = strlen("   auto_completion here");
  memcpy(prompt->auto_completion, "   auto_completion here", prompt->size_completion);

  //initialize counters
  prompt->count_char = 0;
  prompt->count_pos = 0;

  return (prompt);
}
