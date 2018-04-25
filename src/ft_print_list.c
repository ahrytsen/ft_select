/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 17:34:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/25 16:10:33 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	ft_move(t_select *head, t_select **cur, uint64_t buf)
{
	int	i;

	i = 0;
	if (buf == K_UP || buf == K_DOWN)
		*cur = buf == K_UP ? (*cur)->prev : (*cur)->next;
	else if (buf == K_LEFT)
		while (i++ != g_term.height && *cur != head)
			*cur = (*cur)->prev;
	else
		while (i++ != g_term.height && (*cur)->next != head)
			*cur = (*cur)->next;
}

int		check_size(t_select *slist)
{
	int			i;
	int			max_width;
	int			width;
	t_select	*st_p;

	i = 0;
	width = 0;
	max_width = 0;
	st_p = slist;
	while (1)
	{
		if (++i == g_term.height || slist->next == st_p)
		{
			i = 0;
			width += max_width + 3;
			max_width = 0;
		}
		slist->len > max_width ? max_width = slist->len : 0;
		slist = slist->next;
		if (slist == st_p)
			break ;
	}
	return ((width >= g_term.width) ? 0 : 1);
}

void	ft_print_elem(t_select *slist, t_select *cur, int col, int row)
{
	tputs(tgoto(g_term.cm_string, col, row), 1, term_print);
	slist == cur ? tputs(tgetstr("us", NULL), 1, term_print) : 0;
	slist->is_slctd ? tputs(tgetstr("mr", NULL), 1, term_print) : 0;
	ft_dprintf(0, "%s", slist->value);
	slist == cur ? tputs(tgetstr("ue", NULL), 1, term_print) : 0;
	slist->is_slctd ? tputs(tgetstr("me", NULL), 1, term_print) : 0;
}

void	ft_print_list(t_select *slist, t_select *cur)
{
	int			i;
	int			col;
	t_select	*st_p;
	int			max_width;

	i = 0;
	col = 0;
	st_p = slist;
	max_width = 0;
	tputs(g_term.cl_string, 1, term_print);
	while (1)
	{
		if (i == g_term.height)
		{
			i = 0;
			col += max_width + 3;
			max_width = 0;
		}
		ft_print_elem(slist, cur, col, i);
		slist->len > max_width ? max_width = slist->len : 0;
		slist = slist->next;
		i++;
		if (slist == st_p)
			break ;
	}
}
