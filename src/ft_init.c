/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:44:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/23 20:15:38 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_init_terminal(0);
		exit(0);
	}
	return ;
}

void	ft_init_signal(void)
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

void	ft_init_termcap(t_term *env)
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
	env->cl_string = tgetstr("cl", NULL);
	env->cm_string = tgetstr("cm", NULL);
	env->auto_wrap = tgetflag("am");
	env->height = tgetnum("li");
	env->width = tgetnum("co");
	termtype = tgetstr("pc", NULL);
	env->PC = termtype ? *termtype : 0;
	env->BC = tgetstr("le", NULL);
	env->UP = tgetstr("up", NULL);
	tputs(tgetstr("vi", NULL), 1, (int (*)(int))&ft_putchar);
	tputs(tgetstr("ti", NULL), 1, (int (*)(int))&ft_putchar);
}

void	ft_init_terminal(int mod)
{
	static struct termios	savetty;
	static struct termios	tty;

	if (!isatty(0))
		ft_fatal("ft_select: fd isn't valid terminal type device.\n");
	if (!mod)
	{
		tputs(tgetstr("ve", NULL), 1, (int (*)(int))&ft_putchar);
		tputs(tgetstr("te", NULL), 1, (int (*)(int))&ft_putchar);
		tcsetattr(0, TCSANOW, &savetty);
	}
	else if (mod == 1)
	{
		tcgetattr(0, &tty);
		savetty = tty;
		tty.c_lflag &= ~(ICANON | ECHO);
		tty.c_cc[VMIN] = 1;
		tty.c_cc[VTIME] = 0;
	}
	else
		tcsetattr(0, TCSAFLUSH, &tty);
}
