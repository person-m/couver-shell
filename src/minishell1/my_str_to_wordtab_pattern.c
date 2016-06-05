/*
** my_str_to_wordtab_pattern.c for my_str_to_wordtab_pattern in PSU_2015_minishell1
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Sun Jan 24 16:15:23 2016 Vincent COUVERCHEL
** Last update Sun Jun  5 03:53:23 2016 Melvin Personnier
*/

#include "my.h"

static char	*my_strncpy(char *dest, char *src, int n)
{
  int		i;

  i = 0;
  while (i < n && src[i] != '\0')
    {
      dest[i] = src[i];
      i = i + 1;
    }
  dest[i] = '\0';
  return (dest);
}

static char	*my_strndup(char *src, int n)
{
  int		length;
  char		*str;

  length = strlen(src);
  str = my_malloc(length + 1);
  if (str == NULL)
    return (NULL);
  my_strncpy(str, src, n);
  return (str);
}

static int	is_in_str(char *str, char c)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] == c)
	return (1);
      i++;
    }
  return (0);
}

static char	**make_wordtab_pattern(char **array, char *str,
			       char *pattern, int word)
{
  int		i;
  int		start;
  int		count;

  count = 0;
  start = 1;
  i = 0;
  while (str[i])
    {
      while (str[i] && !is_in_str(pattern, str[i]))
	{
	  start = 0;
	  i = i + 1;
	  count = count + 1;
	}
      if (start == 0)
	{
	  array[word] = my_strndup(str + i - count, count);
	  count = 0;
	  word = word + 1;
	}
      while (is_in_str(pattern, str[i]) && str[i] && i++);
    }
  array[word] = NULL;
  return (array);
}

char		**my_str_to_wordtab_pattern(char *str, char *pattern)
{
  int		i;
  int		word;
  int		count;
  char		**array;

  count = 0;
  i = 0;
  word = 0;
  while (str[i])
    {
      if (!is_in_str(pattern, str[i]) && word == 0)
	{
	  count = count + 1;
	  word = 1;
	}
      else if (is_in_str(pattern, str[i]))
	word = 0;
      i = i + 1;
    }
  array = my_malloc(sizeof(char *) * (count + 1));
  if (array == NULL)
    return (NULL);
  array = make_wordtab_pattern(array, str, pattern, 0);
  return (array);
}
