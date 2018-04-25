/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:44:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/25 16:10:24 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

static void	sig_handler(int sig)
{
	struct winsize	w;

	if (sig == SIGINT || sig == SIGABRT || sig == SIGSTOP
		|| sig == SIGKILL || sig == SIGQUIT)
	{
		ft_init_terminal(0);
		exit(0);
	}
	else if (sig == SIGWINCH)
	{
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		g_term.height = w.ws_row;
		g_term.width = w.ws_col;
	}
	else if (sig == SIGTSTP)
	{
		ft_init_terminal(0);
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
	}
	else if (sig == SIGCONT)
		ft_init_terminal(2);
}

static void	ft_init_signal(void)
{
	signal(SIGWINCH, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGSTOP, sig_handler);
	signal(SIGCONT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGKILL, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void		ft_init_termcap(void)
{
	char	*termtype;
	int		success;

	if (!(termtype = getenv("TERM")))
		ft_fatal("Specify a terminal type with `setenv TERM <yourtype>'.\n");
	success = tgetent(NULL, termtype);
	if (success < 0)
		ft_fatal("Could not access the termcap data base.\n");
	else if (!success)
		ft_fatal("Terminal type `%s' is not defined.\n", termtype);
	g_term.cl_string = tgetstr("cl", NULL);
	g_term.cm_string = tgetstr("cm", NULL);
	g_term.auto_wrap = tgetflag("am");
	g_term.height = tgetnum("li");
	g_term.width = tgetnum("co");
}

void		ft_init_terminal(int mod)
{
	static struct termios	savetty;
	static struct termios	tty;

	if (!isatty(0))
		ft_fatal("ft_select: fd isn't valid terminal type device.\n");
	if (!mod)
	{
		tputs(tgetstr("ve", NULL), 1, term_print);
		tputs(tgetstr("te", NULL), 1, term_print);
		tty = savetty;
	}
	else if (mod == 1)
	{
		tcgetattr(0, &tty);
		savetty = tty;
		tty.c_lflag &= ~(ICANON | ECHO);
		tty.c_cc[VMIN] = 1;
		tty.c_cc[VTIME] = 0;
	}
	mod ? ft_init_signal() : 0;
	mod ? tputs(tgetstr("vi", NULL), 1, term_print) : 0;
	mod ? tputs(tgetstr("ti", NULL), 1, term_print) : 0;
	tcsetattr(0, TCSAFLUSH, &tty);
}

t_select	*ft_init_slist(int ac, char **av)
{
	struct stat	buf;
	t_select	*slist;
	t_select	*new;

	slist = NULL;
	while (--ac)
	{
		if (!(new = (t_select*)ft_memalloc(sizeof(t_select))))
			ft_fatal("ft_select: malloc error\n");
		new->value = *++av;
		new->len = ft_strlen(new->value);
		new->st_mode = stat(new->value, &buf) ? S_IFREG : buf.st_mode;
		slist_add(&slist, new);
	}
	return (slist);
}
