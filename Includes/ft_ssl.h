#ifndef FT_SSL_MD5_FT_SSL_H
# define FT_SSL_MD5_FT_SSL_H

# include <readline/readline.h>

# include "ft.h"

enum				e_type
{
	IS_MD5 = 1,
	IS_SHA256
};

typedef struct		s_flags
{
	int				p : 1;
	int				q : 1;
	int				r : 1;
	int				s : 1;
}					t_flags;

typedef struct		s_ssl
{
	t_flags			flags;
	int				type;
}					t_ssl;


#endif
