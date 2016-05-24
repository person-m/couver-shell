/*
** main.c for  in /home/buffat_b/rendu/PSU/PSU_2015_tetris/src
**
** Made by Bertrand BUFFAT
** Login   <buffat_b@epitech.net>
**
** Started on  Mon Mar  7 13:20:39 2016 Bertrand BUFFAT
<<<<<<< HEAD
** Last update Mon May 23 22:33:06 2016 
=======
** Last update Mon May 23 22:30:14 2016 
>>>>>>> buffat_b
*/

#include "shell.h"

void	loop_42sh(t_prompt *prompt)
{
  int	lol = 1;

  while (lol)
    {
      loop_prompt(prompt);
      write(1, "\n", 1);
      write(1, prompt->line, strlen(prompt->line));
      update_prompt(prompt);
    }
}

int		main(void)
{
  t_prompt	*prompt;

  if (!(prompt = init_prompt()))
    return (0);

  ioctl(0, TCSETS, &prompt->non_canon_mode);
  loop_42sh(prompt);
  ioctl(0, TCSETS, &prompt->standard_mode);

  free_prompt(prompt);
  return (0);
}
