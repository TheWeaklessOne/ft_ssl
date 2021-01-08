/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 19:01:18 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/08 22:35:53 by wstygg           ###   ########.fr       */
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
			;
		else
			return (c);
		++str;
	}
	return (0);
}

static void	drop_error(const char *error, const char *str, t_ssl *ssl)
{
	if (str)
	{
		ft_putstr_fd(error, 2);
		ft_putendl_fd(str, 2);
	}
	else
		ft_putendl_fd(error, 2);
	ssl->flags.error = 1;
}

void		check_flags(t_ssl *ssl)
{
	char	*str;
	char	**paths;
	char	*c;

	paths = ssl->argv + 1;
	c = (char[2]){0};
	while (*paths && **paths == '-')
	{
		str = *paths;
		*c = check_symbols(str + 1, &ssl->flags);
		if (ft_strchr(str, 's'))
		{
			if (!*(paths + 1))
				return (drop_error(NO_ARG_ERR, NULL, ssl));
			ssl->flags.strings = list_add_back(ssl->flags.strings, ft_strdup(*++paths));
		}
		if (*c)
			return (drop_error(UNKNOWN_FLAG, c, ssl));
		++paths;
	}
}
