/*
** init_lexer.c for lexer in /Users/couver_v/Epitech/rendu/couver-shell/lexer
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Tue May 24 21:07:17 2016 Vincent COUVERCHEL
** Last update Tue May 24 21:07:17 2016 Vincent COUVERCHEL
*/

int	init_struct(t_lexer *lexer)
{
  lexer->separators[0] = "<<";
  lexer->separators[1] = "<";
  lexer->separators[2] = ">>";
  lexer->separators[3] = ">";
  lexer->separators[4] = "||";
  lexer->separators[5] = "&&";
  lexer->separators[6] = "|";
  lexer->separators[7] = "&";
  lexer->separators[8] = ";";
  lexer->separators[9] = "(";
  lexer->separators[10] = ")";
  lexer->separators[11] = "\"";
  lexer->separators[12] = "'";
  lexer->separators[13] = "`";
  lexer->separators[14] = NULL;
  lexer->pos = 0;
  lexer->len = 0;
  lexer->quote = 0;
  if (!(lexer->command = malloc(sizeof(char *))))
    return (1);
  *lexer->command = NULL;
  return (0);
}
