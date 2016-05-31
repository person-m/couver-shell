/*
** set_term.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 12:08:26 2016
** Last update Tue May 31 13:48:24 2016 Bertrand Buffat
*/

#include "shell.h"

void	get_non_canon(t_prompt *prompt)
{
  tcgetattr(0, &prompt->non_canon_mode);
  prompt->non_canon_mode.c_lflag &= ~ECHO;
  prompt->non_canon_mode.c_lflag &= ~ICANON;
  prompt->non_canon_mode.c_cc[VMIN] = 0;
  prompt->non_canon_mode.c_cc[VTIME] = 1;
  prompt->non_canon_mode.c_oflag &= ~ONLRET;
}

void	get_raw_mode(t_prompt *prompt)
{
  tcgetattr(0, &prompt->raw_mode);
  prompt->raw_mode.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
  | INLCR | IGNCR | ICRNL | IXON);
  prompt->raw_mode.c_oflag &= ~OPOST;
  prompt->raw_mode.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  prompt->raw_mode.c_cflag &= ~(CSIZE | PARENB);
  prompt->raw_mode.c_cflag |= CS8;
}
