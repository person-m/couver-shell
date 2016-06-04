/*
** lexer.c for lexer in /Users/couver_v/Epitech/rendu/couver-shell/lexer
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Tue May 24 21:22:01 2016 Vincent COUVERCHEL
** Last update Thu Jun  2 18:11:17 2016 vincent riamon
*/

#include "shell.h"
#include "lexer.h"
#include "lexer_utils.c"
#include "init_lexer.c"

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
  if (push_subnonstr(lexer, line, *pos, len))
    return (1);
  *pos += len;
  return (0);
}

static void	update_quote(t_lexer *l, char *line)
{
  l->q[0] = (line[l->pos + l->len] != '\"' || l->q[1]) ? l->q[0] : !l->q[0];
  l->q[1] = (line[l->pos + l->len] != '\'' || l->q[0]) ? l->q[1] : !l->q[1];
  l->q[2] = (line[l->pos + l->len] != '`') ? l->q[2] : !l->q[2];
}

static int	lexer_command(char *line, t_lexer *l, int flag)
{
  while (line && (!(l->pos + l->len) || line[l->pos + l->len - 1]))
  {
    update_quote(l, line);
    l->len += (l->escape = ((line[l->pos + l->len] == '\\')
			    && line[l->pos + l->len + 1]));
    if (((!l->q[0] && !l->q[1]) || l->q[2] || line[l->pos + l->len] == '`')
	&& !l->escape && is_special(line[l->pos + l->len]))
    {
      if (push_word(l, line, &l->pos, &l->len) || !(++l->pos))
	return (1);
    }
    else if (!flag && ((l->ret_len = is_separator(l, line + l->pos + l->len))
	     && !l->escape && (((!l->q[0] && !l->q[1]) || l->q[2]
				|| line[l->pos + l->len] == '`')
			       || is_quote(line[l->pos + l->len], l->q))))
    {
      if (push_word(l, line, &l->pos, &l->len)
	  || push_separator(l, line, &l->pos, l->ret_len) || (l->len = 0))
	return (1);
    }
    else
      l->len++;
    }
  return (0);
}

char		**lexer(char *line, int flag)
{
  t_lexer	lexer;

  if (init_struct(&lexer)
      || lexer_command(line, &lexer, flag))
    return (NULL);
//   for (int i = 0; lexer.command[i]; i++)
//       printf("%s\n", lexer.command[i]);
  return (lexer.command);
}
