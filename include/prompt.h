/*
** prompt.h for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 00:11:58 2016
** Last update Thu May 26 13:50:36 2016 
*/

# ifndef _PROMPT_H
# define _PROMPT_H

/*
**	Structure
*/

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <ncurses.h>
# include <term.h>
# undef tab
# include <sys/ioctl.h>
# include <termios.h>

# define TCGETS 0x540d
# define TCSETS 0x540e

struct                  s_caps
{
  char			*up;
  char			*down;
  char			*right;
  char			*left;
  char			*asc;
};

struct                  s_prompt
{
  int                   start_line;
  char                  start_line_str[16];

  char                  *line;
  int                   count_char;
  int                   count_pos;

  char			*prompt;
  int			size_prompt;

  char			*auto_completion;
  int			size_completion;

  char                  *final_line;

  int                   nbcols;
  int                   nblines;

  struct s_caps		*caps;

  struct termios        standard_mode;
  struct termios        non_canon_mode;
  struct termios        raw_mode;
};

typedef struct s_prompt t_prompt;
typedef struct s_caps t_caps;

/*
**	Functions
*/

void            get_non_canon(t_prompt *);
void            get_raw_mode(t_prompt *);

int             get_actual_line(t_prompt *);
void		int_to_str_rec(char *, int, int);
int		size_of_int(int);
void		fill_tab_caps(char *, int, int);

t_prompt        *init_prompt(char **env);

void		clean_screen(t_prompt *);
void            update_prompt(t_prompt *);
void            free_prompt(t_prompt *);

void            aff_prompt(t_prompt *);
void		erase_down_lines(t_prompt *, int);

void            move_cursor(t_prompt *, char *);
void            move_cursor_back(t_prompt *);

void            delete_char(t_prompt *);
void            add_char(t_prompt *, char);

# endif
