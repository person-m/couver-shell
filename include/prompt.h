/*
** prompt.h for  in /home/buffat_b/couver-shell
**
** Made by
** Login   <buffat_b@epitech.net>
**
** Started on  Wed May 25 00:11:58 2016
** Last update Mon May 30 19:21:54 2016 Bertrand Buffat
*/

# ifndef _PROMPT_H
# define _PROMPT_H

/*
**	Structure
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <term.h>
# undef tab
#include <sys/ioctl.h>
#include <termios.h>
#include <dirent.h>

typedef struct		s_caps
{
  char			*up;
  char			*down;
  char			*right;
  char			*left;
  char			*clear;
  char			*ascii;
}			t_caps;

typedef struct		s_prompt
{
  int                   start_line;
  int                   start_col;
  char                  start_line_str[16];

  char                  *line;
  int                   count_char;
  int                   count_pos;

  char			*prompt;
  int			size_prompt;

  char			*auto_completion;
  int			size_completion;
  int			offset;

  int                   nbcols;
  int                   nblines;

  char			**history;
  char			*tmp_history;
  int			curr_history;

  int			nbr;

  struct s_caps		*caps;

  struct termios        standard_mode;
  struct termios        non_canon_mode;
  struct termios        raw_mode;
}			t_prompt;

typedef struct		s_list
{
  int			size;
  char			*name;
  struct s_list		*next;
}			t_list;

/*
**	Functions
*/

void            get_non_canon(t_prompt *);
void            get_raw_mode(t_prompt *);

void            get_actual_line(t_prompt *);
void		int_to_str_rec(char *, int, int);
int		size_of_int(int);
void		fill_tab_caps(char *, int, int);

t_prompt        *init_prompt(char **env, char **hist);

void		clean_screen(t_prompt *);
void		clear_line(t_prompt *);
void            update_prompt(t_prompt *);
void            update_local_prompt(t_prompt *);
void            free_prompt(t_prompt *);

void		aff_line_prompt(t_prompt *);
void            aff_prompt(t_prompt *);
void		erase_down_lines(t_prompt *, int);

void            move_cursor(t_prompt *, char *, char **);
void            move_cursor_back(t_prompt *);

void            add_char(t_prompt *, char);
char		*stradd(char *, char *);

void		bltin_completion(t_prompt *, char **env);
bool		ask_print_commands(int);

int		count_commands(t_prompt *, char **env);
void		print_commands(t_prompt *, char **env, int count);

void		put_nbr(int);
int		dlen(char **);
int		get_offset(char *line, int pos, int *ret);
int		get_offset_directory(char *line, int pos);
void		get_path_from_line(t_prompt *, int offset_dir, char *path);

void		put_in_list(t_list **, char *);
int		get_row_list(t_list **, int);
void		print_dat_list(t_prompt *, t_list *, int);
void		free_list(t_list **);

# endif
