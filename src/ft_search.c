/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 11:31:10 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/27 16:51:14 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_select.h>

static void	search_slist(char *ln)
{
	t_select	*slist;

	slist = g_term.slist_head;
	if (!ln)
		return ;
	while (ft_strncmp(slist->value, ln, ft_strlen(ln)))
	{
		slist = slist->next;
		if (slist == g_term.slist_head)
			return ;
	}
	g_term.slist_cur = slist;
	ft_print_list();
}

static void	sline_tostr(t_sline *sline, char **ln, int mod)
{
	t_sline	*tmp;
	size_t	size;
	char	*line;

	size = 1;
	tmp = sline;
	ft_memdel((void**)ln);
	while (!mod && sline)
	{
		tmp = sline->next;
		free(sline);
		sline = tmp;
	}
	if (!mod || !sline)
		return ;
	while (tmp && ++size)
		tmp = tmp->next;
	if (!(line = ft_memalloc(sizeof(char) * size)))
		ft_fatal(1, ft_exit, "ft_select: malloc error\n");
	while (sline)
	{
		ft_strcat(line, sline->ch);
		sline = sline->next;
	}
	*ln = line;
}

static int	sline_bs(t_sline **sline)
{
	if (!*sline)
		return (0);
	if (!(*sline)->next)
	{
		ft_memdel((void**)sline);
		return (1);
	}
	while ((*sline)->next->next)
		sline = &(*sline)->next;
	ft_memdel((void**)&(*sline)->next);
	return (1);
}

static void	sline_add(t_sline **sline, uint64_t ch)
{
	t_sline	*new_ch;

	if (!(new_ch = ft_memalloc(sizeof(*new_ch))))
		ft_fatal(1, ft_exit, "ft_select: malloc error\n");
	ft_memcpy(new_ch->ch, &ch, 8);
	if (!*sline)
	{
		*sline = new_ch;
		return ;
	}
	while ((*sline)->next)
		sline = &(*sline)->next;
	(*sline)->next = new_ch;
}

void		ft_search(void)
{
	t_sline		*line;
	char		*ln;
	uint64_t	buf;

	line = NULL;
	ln = NULL;
	tputs(tgoto(g_term.curmov, 0, g_term.height), 1, term_print);
	ft_dprintf(0, "Search: ");
	while (!(buf = 0) && read(0, &buf, 8) > 0 && buf != K_RET && buf != K_ESC)
	{
		tputs(tgoto(g_term.curmov, 0, g_term.height), 1, term_print);
		ft_dprintf(0, "Search: %s", ln ? ln : "");
		if (buf == 127 && sline_bs(&line))
			ft_dprintf(0, "%c\033[0J", 8);
		else if (buf == K_UP || buf == K_DOWN
				|| buf == K_RIGHT || buf == K_LEFT)
			ft_dprintf(0, "\a");
		else if (buf != 127 && ft_dprintf(0, "%s", &buf) && buf > 31)
			sline_add(&line, buf);
		sline_tostr(line, &ln, 1);
		search_slist(ln);
	}
	tputs(tgoto(g_term.curmov, 0, g_term.height), 1, term_print);
	tputs(tgetstr("ce", NULL), 1, term_print);
	sline_tostr(line, &ln, 0);
}
