/*
** signals.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 18:13:27 2016
** Last update Tue May 31 22:55:50 2016 Bertrand Buffat
*/

#include "shell.h"

bool	flag_ctrlc = 0;
bool	flag_window = 0;

void	check_signals(t_shell *sh)
{
  char	*term;
  int	total_count;

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

      // get global size of prompt
      total_count = sh->prompt->size_pwd +
      sh->prompt->size_prompt + sh->prompt->count_pos +
      size_of_int(sh->prompt->nbr) + size_of_int(sh->prompt->count_char) + 5;

      //get new start
      get_actual_line(sh->prompt);
      tcsetattr(0, 0, &sh->prompt->non_canon_mode);

      //return to start position
      sh->prompt->start_line -= (total_count / sh->prompt->nbcols);
      sh->prompt->start_col -= (total_count % sh->prompt->nbcols);
 
      //save start position
      fill_tab_caps(sh->prompt->start_line_str, sh->prompt->start_line, sh->prompt->start_col);
      erase_down_lines(sh->prompt, (total_count / sh->prompt->nbcols));
      write(1, sh->prompt->start_line_str, strlen(sh->prompt->start_line_str));

      //get new dimensions
      sh->prompt->nbcols = tigetnum("cols");
      sh->prompt->nblines = tigetnum("lines");

      //security in case of end window
      if (sh->prompt->nblines <= sh->prompt->start_line + (total_count / sh->prompt->nbcols))
	write(1, "\n", 1);

      //clear everything in the line
      clear_line(sh->prompt);
      aff_prompt(sh->prompt);
     
      flag_window = 0;  

    }
}

void			handler(int sig)
{
  if (sig == SIGINT)
    flag_ctrlc = 1;
  if (sig == SIGWINCH)
    flag_window = 1;  
}

void	signal_handler(void)
{
  signal(SIGINT, handler);
  signal(SIGWINCH, handler);
}
