/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:59:05 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/08 23:00:49 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_FT_SSL_H
# define FT_SSL_MD5_FT_SSL_H

# include <readline/readline.h>

# include "ft.h"

# define USAGE "usage: ft_ssl command [-pqr] [-s string] [files ...]"

enum				e_commands
{
	MD5 = 1,
	SHA256,
	COMMANDS_N
};

typedef struct		s_flags
{
	unsigned		p : 1;
	unsigned 		q : 1;
	unsigned 		r : 1;
	unsigned 		error : 1;
	t_list			*strings;
}					t_flags;

typedef struct		s_ssl
{
	t_flags			flags;
	int				command;
	char			**argv;
}					t_ssl;

void				setup_ssl(t_ssl *ssl, char *argv[]);

void				check_flags(t_ssl *ssl);
const char			**get_commands();
void				put_info(const char *command);

void				initialize_readline(void);

#endif
