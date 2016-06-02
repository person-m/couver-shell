/*
** init_lexer.c for lexer in /Users/couver_v/Epitech/rendu/couver-shell/lexer
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Tue May 24 21:07:17 2016 Vincent COUVERCHEL
** Last update Tue May 24 21:07:17 2016 Vincent COUVERCHEL
*/

static char	*add_quote(char *str, unsigned long n)
{
  char		*new;
  int		size;

  size = strlen(str) > n ? n : strlen(str);
  new = my_malloc((size + 3) * sizeof(char));
  new[0] = '\"';
  strncpy(new + 1, str, n);
  new[size + 1] = '\"';
  new[size + 2] = 0;
  return (new);
}

static int	push_substr(t_lexer *lexer, char *line, int pos, int len)
{
  int		ret_len;

  ret_len = tablen(lexer->command);
  if (!(lexer->command
	= realloc(lexer->command, (ret_len + 2)
		  * sizeof(char *))))
    return (1);
  lexer->command[ret_len] = add_quote(line + pos, len);
  del_backslash(lexer->command[ret_len]);
  lexer->command[ret_len + 1] = NULL;
  return (0);
}

static int	push_subnonstr(t_lexer *lexer, char *line, int pos, int len)
{
  int		ret_len;

  ret_len = tablen(lexer->command);
  if (!(lexer->command
	= realloc(lexer->command, (ret_len + 2)
		  * sizeof(char *))))
    return (1);
  lexer->command[ret_len] = strndup(line + pos, len);
  del_backslash(lexer->command[ret_len]);
  lexer->command[ret_len + 1] = NULL;
  return (0);
}

static int	init_struct(t_lexer *lexer)
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
  lexer->q[0] = 0;
  lexer->q[1] = 0;
  lexer->q[2] = 0;
  if (!(lexer->command = malloc(sizeof(char *))))
    return (1);
  *lexer->command = NULL;
  return (0);
}
