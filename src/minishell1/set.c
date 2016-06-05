/*
** builtin5.c for couver-shell in /home/person_m/rendu/PSU/42sh/couver-shell/src/minishell1/
**
** Made by Melvin Personnier
** Login   <person_m@epitech.eu>
**
** Started on  Thu Jun  2 01:51:38 2016 Melvin Personnier
** Last update Sun Jun  5 07:14:00 2016 Melvin Personnier
*/

#include "my.h"

void		create_set(t_shell *sh)
{
  sh->set = my_malloc(sizeof(char *) * 2);
  sh->set[0] = NULL;
}

int		print_set(t_shell *sh)
{
  int		i;

  i = -1;
  write(1, "_\t", 2);
  if (tab_len(sh->history) > 1)
    printf("%s\n\n", sh->history[sh->size_hist - 2]);
  else
    printf("\n");
  while (sh->set[++i])
    printf("%s\n", sh->set[i]);
  return (0);
}

int		is_already_in_set(char **my_set, char *str)
{
  int    	i;
  char		*str2;

  i = 0;
  str2 = my_malloc(sizeof(char) * (strlen(str) + 2));
  str2 = strcpy(str2, str);
  str2[strlen(str)] = '\t';
  str2[strlen(str) + 1] = 0;
  while (my_set[i])
    {
      if (!(strncmp(my_set[i], str2, strlen(str2))))
	{
	  free(str2);
	  return (i);
	}
      i++;
    }
  free(str2);
  return (i);
}

char		*cut_one(char *str)
{
  int		i;
  char		*tmp;

  tmp = my_strdup(str);
  i = -1;
  while (tmp[++i])
    {
      if (tmp[i] == '=' && i != 0)
	{
	  tmp[i] = 0;
	  break ;
	}
    }
  return (tmp);
}

char		*cut_two(char *str)
{
  int		i;
  int		j;
  char		*tmp;

  j = 0;
  i = 0;
  tmp = my_strdup(str);
  while (tmp[i] && tmp[i] != '=')
    i++;
  if (tmp[i] == 0 || i == 0)
    return (NULL);
  else
    {
      i++;
      while (tmp[i])
	tmp[j++] = tmp[i++];
      tmp[j] = 0;
    }
  return (tmp);
}
