#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "ft.h"

typedef struct		s_md5_var
{
	int32_t			a;
	int32_t			b;
	int32_t			c;
	int32_t			d;
}					t_md5_var;

typedef struct		s_md5
{
	int32_t			r[64];
	int32_t			k[64];

	int32_t			h0;
	int32_t			h1;
	int32_t			h2;
	int32_t			h3;
}					t_md5;

#endif
