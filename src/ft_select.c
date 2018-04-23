/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:35:28 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/23 21:07:20 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

int		check_size(t_term *env)
{
	t_select	*slist;
	int			i;
	int			tmp;
	int			max_width;
	int			width;

	i = 0;
	tmp = 0;
	width = 0;
	max_width = 0;
	slist = env->slist;
	while (slist)
	{
		if (++i == env->height)
		{
			i = 0;
			width += max_width + 3;
			max_width = 0;
		}
		tmp = ft_strlen(slist->value);
		tmp > max_width ? max_width = tmp : 0;
		slist = slist->next;
	}
	ft_printf("width: %d\n", env->height);
	if (width >= env->width)
		return (0);
	return (1);
}

int		main(int ac, char **av)
{
	int			i;
	t_term		env;

	i = 1;
	ft_bzero(&env, sizeof(t_term));
	ft_init_terminal(1);
	ft_init_termcap(&env);
	tputs(env.cl_string, 1, (int (*)(int))&ft_putchar);
	check_size(&env);
	while (i < ac)
		slist_add(&env.slist, av[i++]);
	while (env.slist)
	{
		ft_printf("value: %s; id = %u\n", env.slist->value, env.slist->id);
		env.slist = env.slist->next;
	}
	sleep(5);
	ft_init_terminal(0);
}
