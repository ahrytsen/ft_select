/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:35:28 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/24 21:20:39 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

t_term	g_term;

void	main_loop(t_select *head)
{
	t_select	*cur;
	uint64_t	buf;

	cur = head;
	while (!(buf = 0) && read(0, &buf, 8) > 0 && buf != K_RET)
	{
		if (buf == K_SPC )
		{
			cur->is_slctd = !cur->is_slctd;
			cur = cur->next;
		}
		else if (buf == K_BS || buf == K_DEL)
			slist_del(&cur);
		else if (buf == K_UP || buf == K_DOWN
				|| buf == K_LEFT || buf == K_RIGHT)
			ft_move(buf, &cur);
		else
			continue ;
		ft_print_list(head);
	}
}

int		main(int ac, char **av)
{
	t_select	*slist;

	if (!(slist = ft_init_slist(ac, av)))
		return (1);
	ft_init_termcap();
	ft_init_terminal(1);
	ft_print_list(slist);
	main_loop(slist);
	ft_init_terminal(0);
}
