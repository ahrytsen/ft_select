/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pretty_interface.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 17:19:45 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/26 20:08:15 by ahrytsen         ###   ########.fr       */
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
