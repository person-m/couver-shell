/*
** cd.c for cd in /home/riamon_v/rendu/PSU/couver-shell/minishell1
** 
** Made by vincent riamon
** Login   <riamon_v@epitech.net>
** 
** Started on  Sun May 22 17:50:50 2016 vincent riamon
** Last update Mon May 23 18:59:37 2016 vincent riamon
*/

#include "my.h"

static int 	        cd_error(char *str)
{
  struct stat	s;

  if (stat(str, &s) == -1)
    fprintf(stderr, "%s: No such file or directory.\n", str);
  else if (!S_ISDIR(s.st_mode))
    fprintf(stderr, "%s: Not a directory.\n", str);
  else
    fprintf(stderr, "%s: Permissions denied.\n", str);
  return (-1);
}

static void		my_pwd(char **env, char *name, char *pwd)
{
  int		i;

  i = -1;
  while (env[++i] && strncmp(env[i], name, strlen(name)));
  if (!env[i])
    return ;
  free(env[i]);
  env[i] = my_malloc(sizeof(char) * (strlen(name) + strlen(pwd) + 1));
  strconcat(name, pwd, env[i]);
}

static int		basic_cd(char ***env, int mode)
{
  char		*path;
  char		pwd[2000];

  if (mode == 1)
    path = get_var_env(*env, "HOME=");
  else if (mode == 2)
    path = get_var_env(*env, "OLDPWD=");
  if (path)
    {
      getcwd(pwd, 2000);
      if (chdir(path) == 0)
	{
	  my_pwd(*env, "OLDPWD=", pwd);
	  getcwd(pwd, 2000);
	  my_pwd(*env, "PWD=", pwd);
	}
      else
	return (-1);
    }
  return (0);
}

int			cmd_cd(char **tab, char ***env)
{
  char		pwd[2000];

  if (tab_len(tab) > 2)
    {
      fprintf(stderr, "cd: Too many arguments.\n");
      return (-1);
    }
  if (!tab[1])
    return (basic_cd(env, 1));
  else if (!strcmp(tab[1], "-"))
    return (basic_cd(env, 2));
  else
    {
      getcwd(pwd, 2000);
      if (chdir(tab[1]) == 0)
	{
	  my_pwd(*env, "OLDPWD=", pwd);
	  getcwd(pwd, 2000);
	  my_pwd(*env, "PWD=", pwd);
	}
      else
	return (cd_error(tab[1]));
    }
  return (0);
}
