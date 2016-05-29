/*
** parser.h for parser in /Users/couver_v/Epitech/rendu/couver-shell/include
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Sun May 29 11:28:13 2016 Vincent COUVERCHEL
** Last update Sun May 29 11:28:13 2016 Vincent COUVERCHEL
*/

#ifndef PARSER_H_
# define PARSER_H_

# include "lexer.h"

int	is_end_of_command(char *str);
int	is_separator(char *str);
int	is_quote(char *str);
int	is_redirection(char *str);

#endif /* !PARSER_H_ */