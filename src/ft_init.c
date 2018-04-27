/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:44:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/27 12:12:56 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

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
		ft_fatal(1, exit,
				"Specify a terminal type with `setenv TERM <yourtype>'.\n");
	success = tgetent(NULL, termtype);
	if (success < 0)
		ft_fatal(1, exit, "Could not access the termcap data base.\n");
	else if (!success)
		ft_fatal(1, exit, "Terminal type `%s' is not defined.\n", termtype);
	g_term.clear = tgetstr("cl", NULL);
	g_term.curmov = tgetstr("cm", NULL);
	g_term.undln_on = tgetstr("us", NULL);
	g_term.undln_off = tgetstr("ue", NULL);
	g_term.iv_on = tgetstr("mr", NULL);
	g_term.iv_off = tgetstr("me", NULL);
	g_term.height = tgetnum("li");
	g_term.width = tgetnum("co");
}

void		ft_init_terminal(int mod)
{
	static struct termios	savetty;
	static struct termios	tty;

	if (!isatty(0))
		ft_fatal(1, exit, "ft_select: fd isn't valid terminal type device.\n");
	if (!mod)
	{
		tputs(tgetstr("ve", NULL), 1, term_print);
		tputs(tgetstr("te", NULL), 1, term_print);
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
	tcsetattr(0, TCSAFLUSH, mod ? &tty : &savetty);
}

int			ft_init_slist(int ac, char **av)
{
	struct stat	buf;
	t_select	*new;

	while (--ac)
	{
		if (!(new = (t_select*)ft_memalloc(sizeof(t_select))))
			ft_fatal(1, exit, "ft_select: malloc error\n");
		new->value = *++av;
		new->len = ft_strlen(new->value);
		new->st_mode = stat(new->value, &buf) ? 0 : buf.st_mode;
		slist_add(new);
	}
	g_term.slist_cur = g_term.slist_head;
	return (g_term.slist_head ? 0 : -1);
}
