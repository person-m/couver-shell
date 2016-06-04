/*
** variables_utils.c for variables_utils in /Users/couver_v/Epitech/rendu/couver-shell
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Sat Jun  4 13:27:50 2016 Vincent COUVERCHEL
** Last update Sat Jun  4 13:27:50 2016 Vincent COUVERCHEL
*/

int	is_variable(char *str)
{
  while (*str)
  {
    if (*str == '$')
      return (1);
    str++;
  }
  return (0);
}

char	*get_end_bracket(char *str)
{
  while (*str)
  {
    if (*str == '}')
    {
      *str = 0;
      return (str + 1);
    }
    str++;
  }
  fprintf(stderr, "Missing }.\n");
  return (NULL);
}

char	*get_variable_name(char *str, char **end)
{
  int	i;

  i = 0;
  while (str[i] && str[i] != '$')
    i++;
  str[i] = 0;
  *end = (str[++i] == '{' && i++) ? get_end_bracket(str + i) : str + strlen(str);
  return (str + i);
}

int	nb_digit(int nb)
{
  int	count;

  count = 1;
  if (nb < 0)
  {
    nb = -nb;
    count++;
  }
  while (nb >= 10)
  {
    nb *= 0.1;
    count++;
  }
  return (count);
}
