/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slist_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:05:23 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/01 11:35:55 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	slist_add(t_select *new)
{
	if (!g_term.slist_head)
	{
		new->prev = new;
		new->next = new;
		g_term.slist_head = new;
	}
	else
	{
		new->prev = g_term.slist_head->prev;
		new->next = g_term.slist_head;
		g_term.slist_head->prev->next = new;
		g_term.slist_head->prev = new;
	}
	g_term.total++;
}

void	slist_del_cur(void)
{
	t_select	*next;
	t_select	*prev;

	if (!g_term.slist_cur)
		return ;
	next = g_term.slist_cur->next;
	prev = g_term.slist_cur->prev;
	free(g_term.slist_cur);
	if (g_term.slist_cur == next)
	{
		g_term.slist_cur = NULL;
		g_term.slist_head = NULL;
		return ;
	}
	prev->next = next;
	next->prev = prev;
	if (g_term.slist_cur == g_term.slist_head)
	{
		g_term.slist_head = next;
		g_term.slist_cur = next;
	}
	else
		g_term.slist_cur = (next == g_term.slist_head) ? prev : next;
	g_term.total--;
}
