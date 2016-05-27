/*
** check_command_utils.c for check_command_utils in /Users/couver_v/Epitech/rendu/couver-shell/src/parser
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Fri May 27 14:16:32 2016 Vincent COUVERCHEL
** Last update Fri May 27 14:16:32 2016 Vincent COUVERCHEL
*/

static int	is_end_of_command(char *str)
{
  return (!strcmp(str, "||")
	  || !strcmp(str, "&&")
	  || !strcmp(str, "|")
	  || !strcmp(str, ";")
	  || !strcmp(str, "(")
	  || !strcmp(str, ")"));
}

static int	is_separator(char *str)
{
  return (!strcmp(str, "||")
	  || !strcmp(str, "&&")
	  || !strcmp(str, ";")
	  || !strcmp(str, "(")
	  || !strcmp(str, ")"));
}

static int	is_quote(char *str)
{
  return (!strcmp(str, "\"")
	  || !strcmp(str, "'")
	  || !strcmp(str, "`"));
}

static void	go_to_match_arg(char ***command, char *str)
{
  if (is_quote(str))
  {
    while (**command && strcmp(**command, str))
    {
      (*command)++;
    }
    if (**command)
      (*command)++;
  }
  else
    (*command)++;
}

static int	check_match(char **command)
{
  char		*quote[3];
  int		i;
  
  quote[0] = "\"";
  quote[1] = "'";
  quote[2] = "`";
  while (*command)
  {
    i = 0;
    while (i < 3)
    {
      if (!strcmp(*command, quote[i]))
      {
	command++;
	while (*command && strcmp(*command, quote[i]))
	  command++;
	if (!(*command))
	  return (fprintf(stderr, "Unmatched %s.\n", quote[i]) || 1);
      }
      i++;
    }
    command++;
  }
  return (0);
}
