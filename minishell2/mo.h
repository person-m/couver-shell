/*
** mo.h for 42sh in /home/hedia_m/couver-shell/minishell2
** 
** Made by mohamed-laid hedia
** Login   <hedia_m@epitech.net>
** 
** Started on  Fri May 20 22:26:56 2016 mohamed-laid hedia
** Last update Sat May 21 22:06:40 2016 mohamed-laid hedia
*/

#ifndef MO_H_
# define MO_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

typedef struct	s_pipe
{
  int		i;
  int		p[1][2];
}

typedef struct	s_command
{
  int		save[2];
  int		failed;
  int		i;
}		t_command;

#endif  /* !MO_H_ */
