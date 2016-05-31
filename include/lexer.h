/*
** lexer.h for lexer in /Users/couver_v/Epitech/rendu/couver-shell/lexer
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Tue May 24 00:04:58 2016 Vincent COUVERCHEL
** Last update Tue May 24 00:04:58 2016 Vincent COUVERCHEL
*/

#ifndef LEXER_H_
# define LEXER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct		s_lexer
{
  char			*separators[15];
  char			**command;
  int			pos;
  int			len;
  int			ret_len;
  int			escape;
  int			quote;
}			t_lexer;

#endif /* !LEXER_H_ */