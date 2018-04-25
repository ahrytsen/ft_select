/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:35:28 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/25 16:07:45 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

t_term	g_term;

int			term_print(int c)
{
	return (write(0, &c, 1));
}

static void	ft_usage(void)
{
	ft_dprintf(2, "usage: ./ft_select arg1 [arg2 ... argN]\n");
	exit(1);
}

static void	ft_print_res(t_select *slist)
{
	int			i;
	t_select	*st_p;

	i = 0;
	st_p = slist;
	while (1)
	{
		if (slist->is_slctd)
			ft_printf(i ? " %s" : "%s", slist->value);
		slist = slist->next;
		i++;
		if (slist == st_p)
			break ;
	}
}

int	main_loop(t_select *head)
{
	t_select	*cur;
	uint64_t	buf;

	cur = head;
	while (!(buf = 0) && read(0, &buf, 8) > 0 && buf != K_RET && buf != 27 && cur)
	{
		if (buf == K_SPC)
		{
			cur->is_slctd = !cur->is_slctd;
			cur = cur->next;
		}
		else if (buf == K_BS || buf == K_DEL)
			slist_del(head, &cur);
		else if (buf == K_UP || buf == K_DOWN
				|| buf == K_LEFT || buf == K_RIGHT)
			ft_move(head, &cur, buf);
		else
			continue ;
		ft_print_list(head, cur);
	}
	return (buf == K_RET ? 1 : 0);
}

int		main(int ac, char **av)
{
	t_select	*slist;
	int			ret;

	if (!(slist = ft_init_slist(ac, av)))
		ft_usage();
	ft_init_termcap();
	ft_init_terminal(1);
	ft_print_list(slist, slist);
	ret = main_loop(slist);
	ft_init_terminal(0);
	ret ? ft_print_res(slist) : 0;
}
