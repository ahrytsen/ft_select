/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slist_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:05:23 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/24 19:57:50 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	slist_add(t_select **head, t_select *new)
{
	new->prev = new;
	new->next = new;
	if (!*head)
	{
		new->is_cur = 1;
		*head = new;
	}
	else
	{
		new->prev = (*head)->prev;
		new->next = *head;
		(*head)->prev->next = new;
		(*head)->prev = new;
		new->id = new->prev->id + 1;
	}
}

void	slist_del(t_select **elem)
{
	t_select	*next;
	t_select	*prev;

	if (!*elem)
		return ;
	next = (*elem)->next;
	prev = (*elem)->prev;
	free(*elem);
	prev->next = next;
	next->prev = prev;
	*elem = next->id ? next : prev;
}
