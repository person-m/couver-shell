/*
** check_command.c for check_command in /Users/couver_v/Epitech/rendu/couver-shell/src/parser
**
** Made by Vincent COUVERCHEL
** Login   <couver_v@epitech.net>
**
** Started on  Thu May 26 20:49:24 2016 Vincent COUVERCHEL
** Last update Thu May 26 20:49:24 2016 Vincent COUVERCHEL
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "check_command_utils.c"

static int	check_muli_redirections(char **command)
{
  int		left;
  int		right;

  left = 0;
  right = 0;
  while (*command)
  {
    if (!strcmp(">", *command) || !strcmp(">>", *command))
    {
      if (right || !(right = 1))
	return (fprintf(stderr, "Ambiguous output redirect.\n") || 1);
    }
    if (!strcmp("<", *command) || !strcmp("<<", *command))
      if (left || !(left = 1))
	return (fprintf(stderr, "Ambiguous input redirect.\n") || 1);
    if (is_separator(*command))
    {
      left = 0;
      right = 0;
    }
    command++;
  }
  return (0);
}

static int	check_redirection(char **command)
{
  int		pipe;
  int		right;

  pipe = 0;
  right = 0;
  while (*command)
  {
    if (!strcmp("|", *command) && (pipe = 1))
      if (right)
	return (fprintf(stderr, "Ambiguous output redirect.\n") || 1);
    if (!strcmp(">", *command) || !strcmp(">>", *command))
      right = 1;
    if (!strcmp("<", *command) || !strcmp("<<", *command))
      if (pipe)
	return (fprintf(stderr, "Ambiguous input redirect.\n") || 1);
    if (is_separator(*command))
    {
      pipe = 0;
      right = 0;
    }
    command++;
  }
  return (0);
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

static int	check_null_command(char **command)
{
  int		exec;

  exec = 0;
  while (*command)
  {
    if (!strcmp(">", *command) || !strcmp(">>", *command)
	|| !strcmp("<", *command) || !strcmp("<<", *command))
    {
      command++;
      if (*command)
	go_to_match_arg(&command);
    }
    if (!(*command) || is_end_of_command(*command))
    {
      if (!exec)
	return (fprintf(stderr, "Invalid null command.\n") || 1);
      if (*command)
	exec = 0;
    }
    else
      exec = 1;
    if (*command)
      command++;
  }
  return ((exec) ? 0 : (fprintf(stderr, "Invalid null command.\n") || 1));
}

int	check_command(char **command)
{
  if (!(*command))
    return (0);
  return (check_match(command)
	  || check_redirection(command)
	  || check_redirect_name(command)
	  || check_muli_redirections(command)
	  || check_null_command(command));
}
