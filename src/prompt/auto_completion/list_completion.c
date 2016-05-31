/*
** list_completion.c for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Sat May 28 19:04:13 2016
** Last update Tue May 31 13:51:53 2016 Bertrand Buffat
*/

#include "shell.h"

void		put_in_list(t_list **list, char *name)
{
  t_list	*elem;

  if (!(elem = malloc(sizeof(*elem))))
    return ;
  elem->name = strdup(name);
  elem->size = strlen(name);
  elem->next = *list;
  *list = elem;
}

int		get_row_list(t_list **list, int max_size)
{
  t_list	*elem;
  int		len;

  len = 0;
  elem = *list;
  while (elem != NULL)
    {
      if (elem->size > len)
	len = elem->size;
      elem = elem->next;
    }
  if (len == 0)
    return (0);
  return ((max_size / len));
}

void		free_list(t_list **list)
{
  t_list	*elem;
  t_list	*elem2;

  elem = *list;
  while (elem->next != NULL)
    {
      elem2 = elem;
      elem = elem->next;
      free(elem2->name);
      free(elem2);
    }
  free(elem->name);
  free(elem);
}

void	print_dat_list(t_prompt *prompt, t_list *list, int count)
{
  char	empty[1024];
  int	space;
  int	row;
  int	i;

  if (count > prompt->nblines
      && !ask_print_commands(count)
      && write(1, "\n", 1))
    return ;
  if (!(row = get_row_list(&list, prompt->nbcols - 10)))
    return ;
  memset(empty, ' ', 1024);
  space = prompt->nbcols / row;
  i = 0;
  while (list != NULL && ++i)
    {
      write(1, list->name, list->size);
      write(1, empty, space - list->size);
      if (i % row == 0 && !(i = 0))
	write(1, "\n", 1);
      list = list->next;
    }
  write(1, "\n", 1);
}
