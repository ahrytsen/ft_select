/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:35:28 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/17 19:12:21 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

static void	init_terminal_data(void)
{
	char	*termtype;
	int 	success;

	if ((termtype = getenv("TERM"))== NULL)
	{
		ft_dprintf(2, "Specify a terminal type with `setenv TERM <yourtype>'.\n");
		exit(0);
	}
	success = tgetent (term_buffer, termtype);
	if (success < 0)
		ft_dprintf(2, "Could not access the termcap data base.\n");
	if (success == 0)
		ft_dprintf(2, "Terminal type `%s' is not defined.\n", termtype);
}

static void	ft_init(void)
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
}

int		main(int ac, char **av)
{

}
