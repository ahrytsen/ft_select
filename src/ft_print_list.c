/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 17:34:30 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/24 21:22:11 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void			ft_move(uint64_t buf, t_select **cur)
{
	int	dest_id;

	if (buf == K_UP || buf == K_DOWN)
		*cur = buf == K_UP ? (*cur)->prev : (*cur)->next;
	else if (buf == K_LEFT)
	{
		dest_id = (*cur)->id - g_term.height;
		dest_id < 0 ? dest_id = 0 : 0;
		while ((*cur)->id != dest_id)
			*cur = (*cur)->prev;
	}
	else
	{
		dest_id = (*cur)->id + g_term.height;
		while ((*cur)->id != dest_id && (*cur)->next->id != 0)
			*cur = (*cur)->next;
	}
}

int		check_size(t_select *slist)
{
	int			i;
	int			max_width;
	int			width;

	i = 0;
	width = 0;
	max_width = 0;
	while (1)
	{
		if (++i == g_term.height || !slist->next->id)
		{
			i = 0;
			width += max_width + 3;
			max_width = 0;
		}
		slist->len > max_width ? max_width = slist->len : 0;
		slist = slist->next;
		if (!slist->id)
			break ;
	}
	return ((width >= g_term.width) ? 0 : 1);
}

void	ft_print_list(t_select *slist)
{
	int			i;
	int			tmp;
	int			col;
	int			max_width;

	i = 0;
	tmp = 0;
	col = 0;
	max_width = 0;
	while (1)
	{
		if (i == g_term.height)
		{
			i = 0;
			col += max_width + 3;
			max_width = 0;
		}
		tputs(tgoto(g_term.cm_string, col, i), 1, (int (*)(int))&ft_putchar);
		tmp = ft_strlen(slist->value);
		tmp > max_width ? max_width = tmp : 0;
		ft_printf("%s", slist->value);
		slist = slist->next;
		i++;
		if (!slist->id)
			break ;
	}
}

/*void	ft_print_list(t_select *, )
{
	tputs(env.cl_string, 1, (int (*)(int))&ft_putchar);
	}*/
