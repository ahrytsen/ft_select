/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:28:54 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/04/17 18:28:55 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <libft.h>
# include <stdlib.h>

# include <sys/stat.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <dirent.h>
# include <signal.h>
# include <term.h>
# include <fcntl.h>
# include <termios.h>

typedef struct	s_
{
	char	*cmd;
	int		(*ft_builtin)();
}				t_builtins;

/*
int				ft_echo(char **av);
int				ft_cd(char **av);
int				ft_env(char **av);
int				ft_setenv_builtin(char **av);
int				ft_unsetenv_builtin(char **av);
int				ft_exit(char **av);

int				main_loop(void);
int				ft_exec(char **cmd, char *altpath);
t_env			*msh_get_environ(void);
void			ft_env_op(int p);
char			*ft_getenv(const char *name);
int				ft_setenv(const char *name, const char *value, int overwrite);
int				ft_unsetenv(const char *name);
char			*parse_argv(char *line);
char			*parse_line(char *line);
char			**msh_splitsemicolon(char *line);
char			**msh_splitwhitespaces(char *line);
void			ft_slash(t_buf **cur, char **line);
void			ft_bquote(t_buf **cur, char **line);
void			ft_bquote_slash(t_buf **cur, char **line);
void			ft_dquote_slash(t_buf **cur, char **line);
void			ft_bquote_helper(t_buf **cur, char *str);

void			malloc_fail(void);
void			quotes_error(char q);
void			syntax_error(void);

t_buf			*ft_new_mshbuf(void);
void			ft_putstr_mshbuf(t_buf **buf, char *str, ssize_t len);
void			ft_putchar_mshbuf(t_buf **buf, char c);
char			*ft_buftostr(t_buf *buf_head);
void			*ft_free_mshbuf(t_buf *buf);

int				ft_readline(char **line);
char			*cmdline_tostr(t_cmdline *cmdline, int mod);
int				cmdline_bs(t_cmdline *cmdline);
int				cmdline_add(t_cmdline *cmdline, uint64_t buf);
int				cmdline_addch(t_cmdline *cmdline, char ch);
void			cmdline_free(t_cmdline *cmdline);
*/

#endif
