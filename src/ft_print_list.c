/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 17:34:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/27 16:30:36 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

static void	ft_too_small(void)
{
	int					x;
	int					y;
	static const char	*msg = "Sorry, window is too small!";
	static const int	msg_len = 27;

	x = (g_term.width / 2) - (msg_len / 2);
	y = g_term.height / 2;
	x < 0 ? x = 0 : 0;
	tputs(g_term.clear, 1, term_print);
	tputs(tgoto(g_term.curmov, x, y), 1, term_print);
	ft_dprintf(0, "%s", msg);
}

void		ft_check_size(void)
{
	int			i;
	int			max_width;
	int			width;
	t_select	*slist;

	i = 0;
	width = 0;
	max_width = 0;
	slist = g_term.slist_head;
	while (1)
	{
		if (++i == g_term.height - 1 || slist->next == g_term.slist_head)
		{
			i = 0;
			width += max_width + 3;
			max_width = 0;
		}
		slist->len > max_width ? max_width = slist->len : 0;
		slist = slist->next;
		if (slist == g_term.slist_head)
			break ;
	}
	g_term.too_small = (width >= g_term.width) ? 1 : 0;
}

static void	ft_print_elem(t_select *slist, int col, int row)
{
	char	*color;
	char	p;
	char	sl;

	color = ft_color(slist);
	p = slist == g_term.slist_cur ? '>' : ' ';
	sl = slist->is_slctd ? '+' : ' ';
	tputs(tgoto(g_term.curmov, col, row), 1, term_print);
	slist == g_term.slist_cur ? tputs(g_term.undln_on, 1, term_print) : 0;
	slist->is_slctd ? tputs(g_term.iv_on, 1, term_print) : 0;
	ft_dprintf(0, "%c%c%s%s%s", p, sl, color,
			slist->value, *color ? C_EOC : "");
	slist == g_term.slist_cur ? tputs(g_term.undln_off, 1, term_print) : 0;
	slist->is_slctd ? tputs(g_term.iv_off, 1, term_print) : 0;
}

static void	ft_print_column(void)
{
	int			i;
	int			col;
	t_select	*slist;
	int			max_width;

	i = 0;
	col = 0;
	slist = g_term.slist_head;
	max_width = 0;
	while (1)
	{
		if (i == g_term.height - 1)
		{
			i = 0;
			col += max_width + 3;
			max_width = 0;
		}
		ft_print_elem(slist, col, i);
		slist->len > max_width ? max_width = slist->len : 0;
		slist = slist->next;
		i++;
		if (slist == g_term.slist_head)
			break ;
	}
}

void		ft_print_list(void)
{
	g_term.too_small ? ft_too_small() : ft_print_column();
}
