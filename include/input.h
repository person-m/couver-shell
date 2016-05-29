/*
** input.h for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sat May 28 22:37:36 2016
** Last update Sun May 29 00:42:14 2016 
*/

#ifndef INPUT_H
# define INPUT_H

# include "shell.h"

typedef struct  s_input
{
  char          input;
  void          (*ptr)(t_shell *);
}               t_input;

void	check_auto_compet(t_shell *sh);
void	fct_clear(t_shell *sh);
void	delete_char(t_shell *sh);

t_input list_input[] =
  {
    {1, NULL},
    {2, NULL},
    {3, NULL},
    {4, exit_shell},
    {5, NULL},
    {6, NULL},
    {7, NULL},
    {8, NULL},
    {9, check_auto_compet},
    {10, NULL},
    {11, NULL},
    {12, fct_clear},
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
