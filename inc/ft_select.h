/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:28:54 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/23 19:00:01 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <libft.h>
# include <stdlib.h>
# include <sys/stat.h>

# include <sys/param.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <dirent.h>
# include <signal.h>
# include <term.h>
# include <fcntl.h>
# include <termios.h>

typedef struct	s_select
{
	unsigned		id;
	uint8_t			is_slctd;
	char			*value;
	mode_t			st_mode;
	struct s_select	*next;
	struct s_select	*prev;
}				t_select;

typedef struct	s_term
{
	t_select	*slist;
	char		*cl_string;
	char		*cm_string;
	int			height;
	int			width;
	int			auto_wrap;
	char		PC;
	char		*BC;
	char		*UP;
}				t_term;

void			slist_add(t_select **head, char *value);
void			slist_del(t_select **elem);
void			ft_init_signal(void);
void			ft_init_termcap(t_term *env);
void			ft_init_terminal(int mod);

#endif
