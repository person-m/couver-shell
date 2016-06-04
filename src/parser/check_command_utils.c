/*
** check_command_utils.c for check_command_utils in /Users/couver_v/Epitech/rendu/couver-shell/src/parser
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Fri May 27 14:16:32 2016 Vincent COUVERCHEL
** Last update Fri May 27 14:16:32 2016 Vincent COUVERCHEL
*/

static int	is_really_end(char *str)
{
  return (!strcmp(str, "||")
	  || !strcmp(str, "&&")
	  || !strcmp(str, "|")
	  || !strcmp(str, "(")
	  || !strcmp(str, ")"));
}

static int	check_redirect_name(char **command)
{
  while (*command)
  {
    if (!strcmp(">", *command) || !strcmp(">>", *command)
	|| !strcmp("<", *command) || !strcmp("<<", *command))
    {
      command++;
      while (*command && is_quote(*command))
	command++;
      if (!(*command) || is_end_of_command(*command))
      {
	fprintf(stderr, "Missing name for redirect.\n");
	return (1);
      }
    }
    command++;
  }
  return (0);
}

static void	go_to_match_arg(char ***command)
{
  char		*str;

  str = **command;
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

static int	check_quote(char **command, char **quote,
			    char ***max, char ***min)
{
  int		i;

  i = 0;
  while (i < 3)
  {
    if (!strcmp(*command, quote[i]))
    {
      command++;
      while (*command && strcmp(*command, quote[i]) && command != *min)
	command++;
      if ((!(*command) || (command == *min && strcmp(*command, quote[i]))))
	return (fprintf(stderr, "Unmatched %s.\n", quote[i]) || 1);
      *max = (!(*max) && *command) ? command : *max;
      *min = command - 1;
      break;
    }
    i++;
  }
  return (0);
}

static int	check_match(char **command)
{
  char		*quote[3];
  char		**max;
  char		**min;

  quote[0] = "\"";
  quote[1] = "'";
  quote[2] = "`";
  max = NULL;
  min = NULL;
  while (*command)
  {
    if (check_quote(command, quote, &max, &min))
      return (1);
    if (max && command == min)
    {
      command = max;
      max = NULL;
      min = NULL;
    }
    command += !!(*command);
  }
  return (0);
}
