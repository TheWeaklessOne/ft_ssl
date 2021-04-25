/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 19:01:18 by wstygg            #+#    #+#             */
/*   Updated: 2021/04/25 17:27:05 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

#define NO_ARG_ERR "ft_ssl: option requires an argument -- s"
#define UNKNOWN_FLAG "ft_ssl: unknown option - "

static char	check_symbols(const char *str, t_flags *flags)
{
	char	c;

	while (*str)
	{
		c = *str;
		if (c == 'p')
			flags->p = 1;
		else if (c == 'q')
			flags->q = 1;
		else if (c == 'r')
			flags->r = 1;
		else if (c == 's')
			flags->s = 1;
		else
			return (c);
		++str;
	}
	return (0);
}

static int	drop_error(const char *error, const char *str, t_ssl *ssl)
{
	if (str)
	{
		ft_putstr_fd(error, 2);
		ft_putendl_fd(str, 2);
	}
	else
		ft_putendl_fd(error, 2);
	ssl->flags.error = 1;
	return (0);
}

static void	check_file_or_stdin_input(t_ssl *ssl)
{
	int		fd;
	static uint32_t is_tried_to_open_dir = 0;

	if (!*ssl->argv && !ssl->flags.strings && !is_tried_to_open_dir) {
		ssl->flags.strings = list_add_back(ssl->flags.strings, ft_read_file(STDIN_FILENO));
	} else if (*ssl->argv) {
		while (*ssl->argv && **ssl->argv != '-') {
			is_tried_to_open_dir = 1;
			fd = ft_open_file(*ssl->argv);
			if (fd != -1) {
				ssl->flags.strings = list_add_back(ssl->flags.strings, ft_read_file(fd));
			}
			++ssl->argv;
		}
	}
}

static int	flags_loop(t_ssl *ssl)
{
	char	*c;
	char	*str;

	c = (char[2]){0};
	while (*ssl->argv && **ssl->argv == '-') {
		str = *ssl->argv;
		*c = check_symbols(str + 1, &ssl->flags);
		if (ssl->flags.s) {
			if (!*(ssl->argv + 1))
				return (drop_error(NO_ARG_ERR, NULL, ssl));
			ssl->flags.strings = list_add_back(ssl->flags.strings, ft_strdup(*++ssl->argv));
			ssl->flags.s = 0;
		}
		if (*c)
			return (drop_error(UNKNOWN_FLAG, c, ssl));
		++ssl->argv;
	}
	return (1);
}

void		check_flags(t_ssl *ssl)
{
	++ssl->argv;

	while (*ssl->argv) {
		if (!flags_loop(ssl))
			return;
		check_file_or_stdin_input(ssl);
	}
	check_file_or_stdin_input(ssl);
}
