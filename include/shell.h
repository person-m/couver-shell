/*
** shell.h for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:50:52 2016
** Last update Tue May 24 11:50:53 2016 
*/

#ifndef SHELL_H_
# define SHELL_H_

/*
**	Libraries
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "prompt.h"
#include "../src/minishell1/my.h"

typedef struct		s_shell
{
  char			**env;
  char			**cmd;
  char			**alias;
  char			**history;
  t_prompt		*prompt;
}			t_shell;

#endif /* !SHELL_H_ */
