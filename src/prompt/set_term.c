/*
** set_term.c for  in /home/buffat_b/42sh_tmp
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Mon May 23 14:49:08 2016
** Last update Mon May 23 20:05:45 2016 
*/

#include "42sh.h"

void	get_non_canon(t_prompt *prompt)
{
  ioctl(0, TCGETS, &prompt->non_canon_mode);
  prompt->non_canon_mode.c_lflag &= ~ECHO;
  prompt->non_canon_mode.c_lflag &= ~ICANON;
  prompt->non_canon_mode.c_cc[VMIN] = 0;
  prompt->non_canon_mode.c_cc[VTIME] = 0;
}

void	get_raw_mode(t_prompt *prompt)
{
  ioctl(0, TCGETS, &prompt->raw_mode);
  prompt->raw_mode.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
		   | INLCR | IGNCR | ICRNL | IXON);
  prompt->raw_mode.c_oflag &= ~OPOST;
  prompt->raw_mode.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  prompt->raw_mode.c_cflag &= ~(CSIZE | PARENB);
  prompt->raw_mode.c_cflag |= CS8;
}
