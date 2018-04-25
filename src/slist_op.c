/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slist_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:05:23 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/25 14:13:39 by ahrytsen         ###   ########.fr       */
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
	}
}

void	slist_del(t_select *head, t_select **elem)
{
	t_select	*next;
	t_select	*prev;

	if (!*elem)
		return ;
	next = (*elem)->next;
	prev = (*elem)->prev;
	free(*elem);
	if (*elem == next)
	{
		*elem = NULL;
		return ;
	}
	prev->next = next;
	next->prev = prev;
	*elem = next == head ? prev : next;
}
