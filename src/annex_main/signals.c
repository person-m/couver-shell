/*
** signals.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 18:13:27 2016
** Last update Fri Jun  3 16:07:49 2016 Bertrand Buffat
*/

#include "shell.h"

bool	flag_ctrlc = 0;
bool	flag_window = 0;
bool	flag_stop = 0;

void	check_signals(t_shell *sh)
{
  char	*term;

  if (flag_ctrlc)
    {
      memcpy(sh->prompt->line + sh->prompt->count_char, "^C", 2);
      sh->prompt->count_char += 2;
      clean_screen(sh->prompt);
      update_prompt(sh->prompt);
      aff_prompt(sh->prompt);
      flag_ctrlc = 0;
      --sh->prompt->nbr;
    }
  if (flag_window)
    {
      if ((term = get_var_env(sh->env, "TERM=")))
	setupterm(term, 1, (int *)0);
      else
	setupterm("xterm", 1, (int *)0);
      sh->prompt->nbcols = tigetnum("cols");
      sh->prompt->nblines = tigetnum("lines");
      flag_window = 0;
    }
  if (flag_stop)
    {
      write(1, "\n[1]+ Stopped\t\t./42sh\n", 24);
      update_prompt(sh->prompt);
      flag_stop = 0;
    }
}

void			handler(int sig)
{
  if (sig == SIGINT)
    flag_ctrlc = 1;
  if (sig == SIGWINCH)
    flag_window = 1;
  if (sig == SIGSTOP)
    flag_stop = 1;
}

void	signal_handler(void)
{
  signal(SIGINT, handler);
  signal(SIGWINCH, handler);
  signal(SIGSTOP, handler);
}
