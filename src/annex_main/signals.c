/*
** signals.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 18:13:27 2016
** Last update Sun May 29 00:48:56 2016 
*/

#include "shell.h"

bool	flag_signal = 0;

void	check_signals(t_shell *sh)
{
  if (flag_signal)
    {
      clean_screen(sh->prompt);
      update_prompt(sh->prompt);
      aff_prompt(sh->prompt);
      flag_signal = 0;
    }
}

void			handler(int sig)
{
  if (sig == SIGINT)
    flag_signal = 1;
}

void	signal_handler(void)
{
  signal(SIGINT, handler);
}
