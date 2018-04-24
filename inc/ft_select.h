/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:28:54 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/24 21:21:51 by ahrytsen         ###   ########.fr       */
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

# define K_UP 0X415B1B
# define K_DOWN 0X425B1B
# define K_LEFT 0X445B1B
# define K_RIGHT 0X435B1B
# define K_BS 0X7F
# define K_DEL 0X4
# define K_SPC 0X20
# define K_RET 0XA

typedef struct	s_select
{
	int				id;
	uint8_t			is_slctd;
	uint8_t			is_cur;
	char			*value;
	int				len;
	mode_t			st_mode;
	struct s_select	*next;
	struct s_select	*prev;
}				t_select;

typedef struct	s_term
{
	uint8_t		too_small;
	char		*cl_string;
	char		*cm_string;
	int			height;
	int			width;
	int			auto_wrap;
	char		PC;
	char		*BC;
	char		*UP;
}				t_term;

extern t_term	g_term;

void			slist_add(t_select **head, t_select *new);
void			slist_del(t_select **elem);
void			ft_init_termcap(void);
void			ft_init_terminal(int mod);
void			ft_print_list(t_select *slist);
int				check_size(t_select *slist);
t_select		*ft_init_slist(int ac, char **av);
void			ft_move(uint64_t buf, t_select **cur);

#endif
