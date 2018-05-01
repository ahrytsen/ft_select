/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pretty_interface.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:19:45 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/05/01 17:32:59 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

char	*ft_color(t_select *elem)
{
	if (S_ISBLK(elem->st_mode))
		return (C_BLOCK_SP);
	else if (S_ISCHR(elem->st_mode))
		return (C_CHAR_SP);
	else if (S_ISDIR(elem->st_mode))
		return (C_DIR);
	else if (S_ISFIFO(elem->st_mode))
		return (C_PIPE);
	else if (S_ISLNK(elem->st_mode))
		return (C_LINK);
	else if (S_ISSOCK(elem->st_mode))
		return (C_SOCKET);
	else if (elem->st_mode & S_IXUSR)
		return (C_EXEC);
	else if (!elem->st_mode)
		return ("");
	else
		return ("\033[97m");
}

void	ft_print_header(void)
{
	int	b;
	int	i;

	i = 0;
	b = g_term.total > g_term.height ? g_term.height : g_term.total + 3;
	tputs(tgoto(g_term.curmov, 0, 1), 1, term_print);
	ft_dprintf(0, g_term.width > 57 ? "%s %s Total: %d, Selected: %d" : "%s %s",
			"\033[32m|", g_term.width > 27 ? "`./ft_select by ahrytsen`" : "",
			g_term.total, g_term.selected);
	tputs(tgoto(g_term.curmov, g_term.width - 1, 1), 1, term_print);
	ft_dprintf(0, "|");
	while (i < g_term.width)
	{
		tputs(tgoto(g_term.curmov, i, 0), 1, term_print);
		ft_dprintf(0, "=");
		tputs(tgoto(g_term.curmov, i, 2), 1, term_print);
		ft_dprintf(0, "=");
		tputs(tgoto(g_term.curmov, i++, b), 1, term_print);
		!g_term.search ? ft_dprintf(0, "=") : 0;
	}
	ft_dprintf(0, "\033[0m");
	tputs(tgoto(g_term.curmov, 0, b), 1, term_print);
	if (g_term.search)
		ft_dprintf(0, "Search: %.*s",
				g_term.width - 10, g_term.sline ? g_term.sline : "");
}
