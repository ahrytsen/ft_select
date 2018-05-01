/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:35:28 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/01 15:29:36 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

t_term		g_term;

int			term_print(int c)
{
	return (write(0, &c, 1));
}

static void	ft_usage(void)
{
	ft_dprintf(2, "usage: ./ft_select arg1 [arg2 ... argN]\n");
	exit(1);
}

static void	ft_print_res(void)
{
	t_select	*slist;
	int			i;

	i = 0;
	slist = g_term.slist_head;
	while (1)
	{
		if (slist->is_slctd)
			ft_printf(i++ ? " %s" : "%s", slist->value);
		slist = slist->next;
		if (slist == g_term.slist_head)
			break ;
	}
}

int			main(int ac, char **av)
{
	int			ret;

	if (ft_init_slist(ac, av) == -1)
		ft_usage();
	ft_init_termcap();
	ft_init_terminal(1);
	ft_check_size(g_term.slist_head);
	ft_print_list();
	ret = action_loop();
	ft_init_terminal(0);
	ret ? ft_print_res() : 0;
}
