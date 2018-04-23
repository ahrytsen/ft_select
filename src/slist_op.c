/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slist_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:05:23 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/23 20:08:18 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	slist_add(t_select **head, char *value)
{
	t_select	*new;

	if (!(new = (t_select*)ft_memalloc(sizeof(t_select))))
		ft_fatal("ft_select: malloc error\n");
	new->value = value;
	if (!*head)
		*head = new;
	else
	{
		while ((*head)->next)
			head = &(*head)->next;
		new->id = (*head)->id + 1;
		new->prev = *head;
		(*head)->next = new;
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
	if (prev)
		prev->next = next;
	if (next)
		next->prev = next;
	*elem = next ? next : prev;
}
