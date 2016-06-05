/*
** lexer_utils.c for lexer_utils in /Users/couver_v/Epitech/rendu/couver-shell/lexer
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Wed May 25 22:31:04 2016 Vincent COUVERCHEL
** Last update Wed May 25 22:31:04 2016 Vincent COUVERCHEL
*/

static int	tablen(char **array)
{
  int		i;

  i = 0;
  while (array[i])
    i++;
  return (i);
}

static void	del_backslash(char *str)
{
  int		i;
  int		j;
  int		boolean;

  boolean = 0;
  i = 0;
  j = 0;
  while (str[j])
  {
    if (str[j] == '\\' && !boolean)
    {
      boolean = 1;
      j++;
    }
    else
    {
      str[i++] = str[j++];
      boolean = 0;
    }
  }
  str[i] = 0;
}

static int	is_special(char c)
{
  return (!c || c == '\t' || c == ' ' || c == '\n');
}

static int	is_quote(char c, int q[2])
{
  return ((c == '\'' && q[1]) || (c == '\"' && q[0]));
}

static int	is_separator(t_lexer *lexer, char *line)
{
  int		i;

  i = 0;
  while (lexer->separators[i])
  {
    if (!strncmp(lexer->separators[i], line, strlen(lexer->separators[i])))
      return (strlen(lexer->separators[i]));
    i++;
  }
  return (0);
}
