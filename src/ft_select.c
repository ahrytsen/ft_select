/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:35:28 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/18 21:23:17 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

static void	init_terminal_data(void)
{
	char	*termtype;
	int 	success;

	if (!(termtype = getenv("TERM")))
		ft_fatal("Specify a terminal type with `setenv TERM <yourtype>'.\n");
	success = tgetent(NULL, termtype);
	if (success < 0)
		ft_fatal("Could not access the termcap data base.\n");
	else if(!success)
		ft_fatal("Terminal type `%s' is not defined.\n", termtype);
}

/*static void	ft_init(void)
{
	int			shlvl;
	char		*tmp;

	shlvl = tmp ? ft_atoi(tmp) : 0;
	tmp = ft_itoa(shlvl + 1);
	ft_setenv("SHLVL", tmp, 1);
	free(tmp);
	ft_setenv("PATH", "/usr/bin:/bin", 0);
	signal(SIGINT, sig_handler);
	signal(SIGWINCH, SIG_IGN);
	signal(SIGINFO, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	}*/

int		main(int ac, char **av)
{
	int			i;
	t_select	*slist;

	i = 1;
	slist = NULL;
	init_terminal_data();
	while (i < ac)
		slist_add(&slist, av[i++]);
	while (slist)
	{
		ft_printf("value: %s; id = %u\n", slist->value, slist->id);
		slist = slist->next;
	}

}
