/*
** init_prompt.c for  in /home/buffat_b/couver-shell/src/prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:56:28 2016
** Last update Sun May 29 03:25:19 2016 
*/

#include "shell.h"

void	free_prompt(t_prompt *prompt)
{
  free(prompt->line);
  free(prompt->prompt);
  free(prompt->auto_completion);
  free(prompt->caps);
  free(prompt);
}

t_caps		*init_caps(void)
{
  t_caps	*caps;
  char		*smkx;
  char		*tmp;
  char		*tmp2;

  if (!(caps = malloc(sizeof(*caps)))
      || !(caps->up = tigetstr("kcuu1"))
      || !(caps->down = tigetstr("kcud1"))
      || !(caps->left = tigetstr("kcub1"))
      || !(caps->right = tigetstr("kcuf1"))
      || !(caps->clear = tigetstr("clear"))
      || !(smkx = tigetstr("smkx")))
    return (NULL);
  if (!(tmp = strdup("a,a:b,b:c,c:d,d:e,e:f,f:g,g:h,h:i,i:j,j:k,k:l,l:m,m:")))
    return (NULL);
  if (!(tmp2 = strdup("n,n:o,o:p,p:q,q:r,r:s,s:t,t:u,u:v,v:w,w:x,x:y,y:z,z")))
    return (NULL);
  if (!(caps->ascii = strcat(tmp, tmp2)))
    return (NULL);
  write(1, smkx, strlen(smkx));
  return (caps);
}

void		init_prompt_line(t_prompt *prompt)
{
  prompt->size_prompt = strlen("Ceci est un prompt > ");
  memcpy(prompt->prompt, "Ceci est un prompt > ", prompt->size_prompt);
}

void		set_info_term(t_prompt *prompt, char **env)
{
  char		*term;

  if ((term = get_var_env(env, "TERM=")))
    setupterm(term, 1, (int *)0);
  else
    setupterm("xterm", 1, (int *)0);

  ioctl(0, TCGETS, &prompt->standard_mode);
  get_non_canon(prompt);
  get_raw_mode(prompt);
}

t_prompt	*init_prompt(char **env)
{
  t_prompt	*prompt;
  int		size;

  if (!(prompt = malloc(sizeof(*prompt))))
    return (NULL);

  set_info_term(prompt, env);

  if (!(prompt->caps = init_caps()))
    return (NULL);
  prompt->nbcols = tigetnum("cols");
  prompt->nblines = tigetnum("lines");

  size = prompt->nbcols * prompt->nblines;
  if (!(prompt->prompt = malloc(sizeof(char) * size))
      || (!(prompt->line = malloc(sizeof(char) * size)))
      || (!(prompt->auto_completion = malloc(sizeof(char) * size))))
    return (NULL);

  init_prompt_line(prompt);
  update_prompt(prompt);

  return (prompt);
}
