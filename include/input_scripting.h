/*
** input_scripting.h for  in /home/buffat_b/couver-shell
** 
** Made by Bertrand Buffat
** Login   <buffat_b@epitech.net>
** 
** Started on  Thu Jun  2 20:02:38 2016 Bertrand Buffat
** Last update Fri Jun  3 15:52:44 2016 Bertrand Buffat
*/

#ifndef INPUT_SCRIPTING_H
# define INPUT_SCRIPTING_H

# include "shell.h"

typedef struct  s_input
{
  char		input;
  void		(*ptr)(t_shell *);
}               t_input;

void	delete_char(t_shell *sh);
void	exit_script(t_shell *sh);

t_input list_script_input[] =
  {
    {1, NULL},
    {2, NULL},
    {3, NULL},
    {4, exit_script},
    {5, NULL},
    {6, NULL},
    {7, NULL},
    {8, NULL},
    {9, NULL},
    {10, NULL},
    {11, NULL},
    {12, NULL},
    {13, NULL},
    {14, NULL},
    {15, NULL},
    {16, NULL},
    {17, NULL},
    {18, NULL},
    {19, NULL},
    {20, NULL},
    {21, NULL},
    {22, NULL},
    {23, NULL},
    {24, NULL},
    {25, NULL},
    {26, NULL},
    {27, NULL},
    {28, NULL},
    {29, NULL},
    {30, NULL},
    {31, NULL},
    {127, delete_char},
    {0, NULL},
  };

#endif
