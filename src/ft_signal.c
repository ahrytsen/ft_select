/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 21:02:41 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/01 16:17:04 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

static void	ft_susp(void)
{
	ft_init_terminal(0);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
}

static void	ft_winch(void)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	g_term.height = w.ws_row;
	g_term.width = w.ws_col;
	ft_check_size(g_term.slist_head);
	ft_print_list();
}

static void	ft_cont(void)
{
	ft_init_terminal(2);
	ft_winch();
}

static void	ft_kill(void)
{
	ft_init_terminal(0);
	exit(0);
}

void		sig_handler(int sig)
{
	if (sig == SIGINT || sig == SIGABRT || sig == SIGSTOP
		|| sig == SIGKILL || sig == SIGQUIT)
		ft_kill();
	else if (sig == SIGWINCH)
		ft_winch();
	else if (sig == SIGTSTP && isatty(1))
		ft_susp();
	else if (sig == SIGCONT)
		ft_cont();
}
