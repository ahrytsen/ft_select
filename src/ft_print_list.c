/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 17:34:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/01 17:26:09 by ahrytsen         ###   ########.fr       */
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

void		ft_check_size(t_select *slist)
{
	int			i;
	int			max_width;
	int			width;

	i = 3;
	width = 0;
	max_width = 0;
	g_term.col_width = 0;
	while (1)
	{
		slist->len > max_width ? max_width = slist->len : 0;
		slist->len > g_term.col_width ? g_term.col_width = slist->len : 0;
		slist = slist->next;
		if (++i >= g_term.height - 1 || slist == g_term.slist_head)
		{
			i = 3;
			width += max_width + 3;
			max_width = 0;
		}
		if (slist == g_term.slist_head)
			break ;
	}
	g_term.too_small = (width > g_term.width || g_term.height < 5) ? 1 : 0;
	g_term.col_width + 2 < g_term.width && g_term.height > 4 && g_term.too_small
		? g_term.too_small = 2 : 0;
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

static void	ft_print_column(t_select *col_head)
{
	int			i;
	int			col;
	int			max_width;
	t_select	*slist;

	i = 3;
	col = 0;
	max_width = 0;
	slist = col_head;
	while (1)
	{
		ft_print_elem(slist, col, i);
		slist->len > max_width ? max_width = slist->len : 0;
		slist = slist->next;
		i++;
		if (i == g_term.height - 1 || slist == g_term.slist_head)
		{
			i = 3;
			col += max_width + 3;
			max_width = 0;
		}
		if (slist == col_head
			|| (i == 3 && col + g_term.col_width + 3 > g_term.width))
			break ;
	}
}

void		ft_print_list(void)
{
	int			i;
	t_select	*slist;
	t_select	*col_head;

	i = 3;
	slist = g_term.slist_head;
	tputs(g_term.clear, 1, term_print);
	ft_print_header();
	if (g_term.too_small == 1)
		ft_too_small();
	else if (!g_term.too_small)
		ft_print_column(slist);
	else
	{
		while (1)
		{
			i == g_term.height - 1 ? i = 3 : 0;
			i++ == 3 ? col_head = slist : 0;
			if (slist == g_term.slist_cur)
				break ;
			slist = slist->next;
		}
		ft_print_column(col_head);
	}
}
