/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:28:54 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/01 17:36:51 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <libft.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

# include <sys/param.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <dirent.h>
# include <signal.h>
# include <term.h>
# include <fcntl.h>
# include <termios.h>

/*
**	KEY BINDINGS
*/
# define K_UP 0X415B1B
# define K_DOWN 0X425B1B
# define K_LEFT 0X445B1B
# define K_RIGHT 0X435B1B
# define K_BS 0X7F
# define K_DEL 0X4
# define K_SPC 0X20
# define K_RET 0XA
# define K_SRCH 0X6
# define K_ESC 0X1B

/*
**	FILE TYPES COLORS
*/
# define C_BLOCK_SP "\033[46m\033[34m"
# define C_CHAR_SP "\033[43m\033[34m"
# define C_DIR "\033[1;96m"
# define C_PIPE "\033[33m"
# define C_LINK "\033[35m"
# define C_SOCKET "\033[32m"
# define C_EXEC "\033[31m"
# define C_EOC "\033[0m"

typedef struct	s_select
{
	uint8_t			is_slctd;
	char			*value;
	int				len;
	mode_t			st_mode;
	struct s_select	*next;
	struct s_select	*prev;
}				t_select;

typedef struct	s_term
{
	uint8_t		too_small;
	uint8_t		search;
	char		*sline;
	int			col_width;
	char		*clear;
	char		*curmov;
	char		*undln_on;
	char		*undln_off;
	char		*iv_on;
	char		*iv_off;
	int			total;
	int			selected;
	int			height;
	int			width;
	t_select	*slist_cur;
	t_select	*slist_head;
}				t_term;

typedef struct	s_sline
{
	char			ch[9];
	struct s_sline	*next;
}				t_sline;

extern t_term	g_term;

/*
**				ft_select.c
*/
int				term_print(int c);
/*
**				slist_op.c
*/
void			slist_add(t_select *new);
void			slist_del_cur(void);
/*
**				ft_init.c
*/
void			ft_init_termcap(void);
void			ft_init_terminal(int mod);
int				ft_init_slist(int ac, char **av);
/*
**				ft_print_list.c
*/
void			ft_print_list(void);
void			ft_check_size(t_select *slist);
/*
**				ft_signal.c
*/
void			sig_handler(int sig);
/*
**				ft_action.c
*/
int				action_loop(void);
void			ft_exit(int st);
/*
**				ft_pretty_interface.c
*/
char			*ft_color(t_select *elem);
void			ft_print_header(void);
/*
**				ft_search.c
*/
void			ft_search(void);

#endif
