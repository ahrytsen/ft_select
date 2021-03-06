/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 19:10:51 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/01 16:44:33 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void		ft_exit(int st)
{
	ft_init_terminal(0);
	exit(st);
}

static void	ft_select(int mod)
{
	t_select	*slist;

	slist = g_term.slist_head;
	g_term.selected = mod ? g_term.total : 0;
	while (1)
	{
		slist->is_slctd = mod;
		slist = slist->next;
		if (slist == g_term.slist_head)
			break ;
	}
}

static void	ft_move(uint64_t buf)
{
	int	i;

	i = 0;
	if (buf == K_UP)
		g_term.slist_cur = g_term.slist_cur->prev;
	else if (buf == K_DOWN)
		g_term.slist_cur = g_term.slist_cur->next;
	else if (buf == K_LEFT)
		while (i++ != g_term.height - 4
			&& g_term.slist_cur != g_term.slist_head)
			g_term.slist_cur = g_term.slist_cur->prev;
	else
		while (i++ != g_term.height - 4
			&& g_term.slist_cur->next != g_term.slist_head)
			g_term.slist_cur = g_term.slist_cur->next;
}

static int	action_loop_helper(uint64_t buf)
{
	if (buf == 'a')
		ft_select(1);
	else if (buf == 'A')
		ft_select(0);
	else if (buf == K_SRCH)
	{
		g_term.search = 1;
		ft_search();
		g_term.search = 0;
	}
	else
		return (1);
	return (0);
}

int			action_loop(void)
{
	uint64_t	buf;

	while (g_term.slist_cur && !(buf = 0) && read(0, &buf, 8) > 0
		&& (buf != K_RET || g_term.too_small) && buf != K_ESC)
	{
		if (buf == K_SPC && g_term.too_small != 1)
		{
			g_term.slist_cur->is_slctd = !g_term.slist_cur->is_slctd;
			g_term.slist_cur->is_slctd ? g_term.selected++ : g_term.selected--;
			g_term.slist_cur = g_term.slist_cur->next;
		}
		else if ((buf == K_BS || buf == K_DEL) && g_term.too_small != 1)
		{
			slist_del_cur();
			tputs(g_term.clear, 1, term_print);
		}
		else if (g_term.too_small != 1 && (buf == K_UP || buf == K_DOWN
				|| buf == K_LEFT || buf == K_RIGHT))
			ft_move(buf);
		else if (action_loop_helper(buf) || g_term.too_small == 1)
			continue ;
		g_term.slist_cur ? ft_print_list() : 0;
	}
	return (buf == K_RET && !g_term.too_small ? 1 : 0);
}
