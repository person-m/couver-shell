/*
** lexer.c for lexer in /Users/couver_v/Epitech/rendu/couver-shell/lexer
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Tue May 24 21:22:01 2016 Vincent COUVERCHEL
** Last update Tue May 24 21:22:01 2016 Vincent COUVERCHEL
*/

#include "lexer.h"
#include "init_lexer.c"
#include "lexer_utils.c"

static int	push_substr(t_lexer *lexer, char *line, int pos, int len)
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

static int	push_word(t_lexer *lexer, char *line, int *pos, int *len)
{
  if (*len > 0)
  {
    if (push_substr(lexer, line, *pos, *len))
      return (1);
    *pos += *len;
    *len = 0;
  }
  return (0);
}

static int	push_separator(t_lexer *lexer, char *line, int *pos, int len)
{
  if (push_substr(lexer, line, *pos, len))
    return (1);
  *pos += len;
  return (0);
}

static int	lexer_command(char *line, t_lexer *lexer)
{
  int		pos;
  int		len;
  int		ret_len;
  int		escape;

  pos = 0;
  len = 0;
  while (!(pos + len) || line[pos + len - 1])
  {
    len += (escape = ((line[pos + len] == '\\') && line[pos + len + 1]));
    if (!escape && is_special(line[pos + len]))
    {
      if (push_word(lexer, line, &pos, &len) || !(++pos))
	return (1);
    }
    else if (!escape && (ret_len = is_separator(lexer, line + pos + len)))
    {
      if (push_word(lexer, line, &pos, &len)
	  || push_separator(lexer, line, &pos, ret_len) || (len = 0))
	return (1);
    }
    else
      len++;
  }
  return (0);
}

char		**lexer(char *line)
{
  t_lexer	lexer;

  if (init_struct(&lexer)
      || lexer_command(line, &lexer))
    return (NULL);
  return (lexer.command);
}
