/*
** signals.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 18:13:27 2016
** Last update Thu May 26 15:58:01 2016 
*/

#include "shell.h"

bool	flag_exit = 0;
bool	flag_signal = 0;

void	check_signals(t_shell *sh)
{

  //if ctrl Z
  if (flag_exit)
    exit_shell(sh, sh->ret);

  //if ctrl C
  if (flag_signal)
    {
      clean_screen(sh->prompt);
      update_prompt(sh->prompt);
    }

  flag_signal = 0;
}

void			handler(int sig)
{
  flag_signal = 1;

  if (sig == SIGTSTP)
    flag_exit = 1;

  if (sig == SIGINT)
    (void)sig;

}

void	signal_handler(void)
{
  signal(SIGINT, handler);
  signal(SIGTSTP, handler);
}
