#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "ft.h"

typedef struct	s_md5
{
	unsigned	*abcd;
	unsigned	*aabbccdd;
	unsigned	*shifts;
	unsigned	*constants;
}				t_md5;

char				*do_md5(const unsigned char *data);

#endif
