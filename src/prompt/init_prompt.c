/*
** init_prompt.c for  in /home/buffat_b/couver-shell/src/prompt
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Tue May 24 11:56:28 2016
** Last update Wed Jun  1 23:23:13 2016 Bertrand Buffat
*/

#include "shell.h"

void	free_prompt(t_prompt *prompt)
{
  if (prompt->tmp_history)
    free(prompt->tmp_history);
  free(prompt->line);
  free(prompt->prompt);
  free(prompt->auto_completion);
  free(prompt->caps->ascii);
  free(prompt);
}

t_caps		*init_caps(void)
{
  t_caps	*caps;
  char		*smkx;

  if (!(caps = malloc(sizeof(*caps)))
      || !(caps->up = tigetstr("kcuu1"))
      || !(caps->down = tigetstr("kcud1"))
      || !(caps->left = tigetstr("kcub1"))
      || !(caps->right = tigetstr("kcuf1"))
      || !(caps->clear = tigetstr("clear"))
      || !(smkx = tigetstr("smkx")))
    return (NULL);
  if (!(caps->ascii =
	strdup("a,a:b,b:c,c:d,d:e,e:f,f:g,g:h,h:i,i:j,j:k,k:l,l:m,m:"))
      || !(caps->ascii =
	   stradd(caps->ascii,
		  "n,n:o,o:p,p:q,q:r,r:s,s:t,t:u,u:v,v:w,w:x,x:y,y:z,z:"))
      || !(caps->ascii =
	   stradd(caps->ascii,
		  "A,A:B,B:C,C:D,D:E,E:F,F:G,G:H,H:I,I:J,J:K,K:L,L:M,M:"))
      || !(caps->ascii =
	   stradd(caps->ascii,
		  "N,N:O,O:P,P:Q,Q:R,R:S,S:T,T:U,U:V,V:W,W:X,X:Y,Y:Z,Z")))
    return (NULL);
  write(1, smkx, strlen(smkx));
  return (caps);
}

void	init_prompt_line(t_prompt *prompt, char **env)
{
  char	*name;

  if (!(name = get_var_env(env, "USER=")))
    {
      prompt->size_prompt = 13;
      memcpy(prompt->prompt, "User unknown ", prompt->size_prompt);
    }
  else
    {
      prompt->size_prompt = strlen(name);
      memcpy(prompt->prompt, name, prompt->size_prompt);
      memcpy(prompt->prompt + prompt->size_prompt, " ", 1);
      ++prompt->size_prompt;
    }
  prompt->nbr = 0;
}

void	set_info_term(t_prompt *prompt, char **env)
{
  char	*term;

  if ((term = get_var_env(env, "TERM=")))
    setupterm(term, 1, (int *)0);
  else
    setupterm("xterm", 1, (int *)0);
  tcgetattr(0, &prompt->standard_mode);
  get_non_canon(prompt);
  get_raw_mode(prompt);
}

t_prompt	*init_prompt(char **env, char **history)
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
      || (!(prompt->auto_completion = malloc(sizeof(char) * size)))
      || (!(prompt->pwd = malloc(sizeof(char) * size))))
    return (NULL);
  init_prompt_line(prompt, env);
  prompt->tmp_history = NULL;
  prompt->history = history;
  prompt->env = env;
  get_pwd_prompt(prompt);
  update_prompt(prompt);
  return (prompt);
}
