/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:59:05 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/03 19:59:05 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_FT_SSL_H
# define FT_SSL_MD5_FT_SSL_H

# include <readline/readline.h>

# include "ft.h"

# define USAGE "usage: ft_ssl command [-pqr] [-s string] [files ...]"

enum				e_type
{
	IS_MD5 = 1,
	IS_SHA256
};

typedef struct		s_flags
{
	unsigned		p : 1;
	unsigned		q : 1;
	unsigned		r : 1;
	unsigned		s : 1;
	char			*string;
}					t_flags;

typedef struct		s_ssl
{
	t_flags			flags;
	int				type;
}					t_ssl;

#endif
