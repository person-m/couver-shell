/*
** globbing_utils.c for globbing_utils in /Users/couver_v/Epitech/rendu/couver-shell/src/globbing
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Sun May 29 16:54:59 2016 Vincent COUVERCHEL
** Last update Sun May 29 16:54:59 2016 Vincent COUVERCHEL
*/

//static int	get_next_match_arg(char **command, int i)
//{
//  char		*str;
//
//  str = command[i];
//  if (is_quote(str))
//  {
//    i++;
//    while (command[i] && strcmp(command[i], str))
//      i++;
//    i += !!(command[i]);
//  }
//  else
//    i++;
//  return (i);
//}

static int	tablen(char **array)
{
  int		i;

  i = 0;
  while (array && array[i])
    i++;
  return (i);
}

static	void	wordtabncpy(char **dest, char **src, int n)
{
  int		i;

  i = 0;
  while (src && i < n && src[i])
  {
    dest[i] = strdup(src[i]);
    i++;
  }
  dest[i] = NULL;
}

//static int	is_exec(char **command, int i)
//{
//  return (!is_separator(command[i]) && !is_redirection(command[i])
//	  && ((i >= 2 && is_redirection(command[i - 2]))
//	      || (i >= 1 && is_separator(command[i - 1]))
//	      || (i == 0)));
//}

//static int	is_redirection_arg(char **command, int i)
//{
//  return (i > 0 && is_redirection(command[i - 1]));
//}
