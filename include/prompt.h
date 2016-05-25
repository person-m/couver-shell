/*
** prompt.h for  in /home/buffat_b/couver-shell/include
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Mon May 23 20:55:48 2016
** Last update Tue May 24 23:50:23 2016 
*/

# ifndef _PROMPT_H
# define _PROMPT_H

/*
**	Structure
*/

#include <ncurses.h>
#include <term.h>
#include <sys/ioctl.h>
#include <termios.h>

struct                  s_prompt
{
  int                   start_line;
  char                  *start_line_str;

  char                  *line;
  char                  *final_line;

  char			*prompt;
  int			size_prompt;

  char			*auto_completion;
  int			size_completion;

  int                   count_char;
  int                   count_pos;

  int                   nbcols;
  int                   nblines;

  struct termios        standard_mode;
  struct termios        non_canon_mode;
  struct termios        raw_mode;
};

typedef struct s_prompt t_prompt;

/*
**	Functions
*/

void            get_non_canon(t_prompt *);
void            get_raw_mode(t_prompt *);

void            str(char *);
char            *str_dup(char *);
char            *str_cat(char *, char *);
void		int_to_str_rec(char *, int, int);
char            *int_to_str(int);

int             get_actual_line(t_prompt *);
void            free_prompt(t_prompt *);
t_prompt        *init_prompt(void);
void            update_prompt(t_prompt *);

void            aff_prompt(t_prompt *);
char            get_input(t_prompt *);
void            which_input(t_prompt *, char);
void            loop_prompt(t_prompt *);

void            move_cursor(t_prompt *, char *);
void            move_cursor_back(t_prompt *);

void            delete_char(t_prompt *);
void            add_char(t_prompt *, char);

# endif
