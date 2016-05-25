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

  i = 0;
  j = 0;
  while (str[j])
  {
    if (str[j] != '\\')
      str[i++] = str[j++];
    else
      j++;
  }
  str[i] = 0;
}

static int		is_special(char c)
{
  return (!c || c == '\t' || c == ' ');
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
