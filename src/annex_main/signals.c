/*
** signals.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 18:13:27 2016
** Last update Mon May 30 13:32:56 2016 Bertrand Buffat
*/

#include "shell.h"

bool	flag_signal = 0;

void	check_signals(t_shell *sh)
{
  if (flag_signal)
    {
      memcpy(sh->prompt->line + sh->prompt->count_char, "^C", 2);
      sh->prompt->count_char += 2;
      clean_screen(sh->prompt);
      update_prompt(sh->prompt);
      aff_prompt(sh->prompt);
      flag_signal = 0;
      --sh->prompt->nbr;
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
