#include "md5.h"
#include <stdbool.h>

# define TRUE		1
# define FALSE		0

typedef char						t_bool;
typedef void *						t_pvoid;
typedef char *						t_pchar;
typedef const char *				t_cpchar;
typedef unsigned char *				t_puchar;
typedef const unsigned char *		t_cpuchar;
typedef unsigned int				t_uint;
typedef long long					t_long;

# define LEFTROTATE(x, c)		(((x) << (c)) | ((x) >> (32 - (c))))

static void			ft_md5_loop_main_i(t_md5_var *var, uint32_t *f,
										  uint32_t *g, t_uint i)
{
	if (i < 16)
	{
		*f = ((*var).b & (*var).c) | ((~(*var).b) & (*var).d);
		*g = i;
	}
	else if (i < 32)
	{
		*f = ((*var).d & (*var).b) | ((~(*var).d) & (*var).c);
		*g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		*f = (*var).b ^ (*var).c ^ (*var).d;
		*g = (3 * i + 5) % 16;
	}
	else
	{
		*f = (*var).c ^ ((*var).b | (~(*var).d));
		*g = (7 * i) % 16;
	}
}

static void			ft_md5_loop_main(t_md5 md5, const int *w, t_md5_var *var)
{
	uint32_t	f;
	uint32_t	g;
	uint32_t	tmp;
	t_uint		i;

	i = 0;
	while (i < 64)
	{
		ft_md5_loop_main_i(var, &f, &g, i);
		tmp = (*var).d;
		(*var).d = (*var).c;
		(*var).c = (*var).b;
		(*var).b = (LEFTROTATE(((*var).a + f + md5.k[i] + w[g]), md5.r[i])) +
				   (*var).b;
		(*var).a = tmp;
		i = i + 1;
	}
}

extern t_bool		ft_md5_loop(t_md5 *md5, t_puchar block, size_t size)
{
	size_t		offset;
	int			*w;
	t_md5_var	var;

	offset = 0;
	while (offset < size)
	{
		w = (int *)(block + offset);
		var.a = (*md5).h0;
		var.b = (*md5).h1;
		var.c = (*md5).h2;
		var.d = (*md5).h3;
		ft_md5_loop_main(*md5, w, &var);
		(*md5).h0 += var.a;
		(*md5).h1 += var.b;
		(*md5).h2 += var.c;
		(*md5).h3 += var.d;
		offset = offset + 64;
	}
	return (TRUE);
}

static void			ft_md5_init_set_r(t_md5 *md5, t_uint n,
										 const int32_t tab[4])
{
	t_uint		i;

	i = n;
	while (i - n < 16)
	{
		(*md5).r[i] = tab[(i - n) % 4];
		i = i + 1;
	}
}

static void			ft_md5_init_set_k(t_md5 *md5)
{
	t_uint			n;
	const uint32_t	k[] = {
			0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
			0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
			0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
			0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
			0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
			0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
			0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
			0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
			0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
			0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
			0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
			0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
			0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
			0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
			0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
			0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	n = 0;
	while (n < 64)
	{
		(*md5).k[n] = k[n];
		n = n + 1;
	}
}

extern t_bool		ft_md5_init(t_md5 *md5)
{
	const int32_t		t0[4] = {7, 12, 17, 22};
	const int32_t		t1[4] = {5, 9, 14, 20};
	const int32_t		t2[4] = {4, 11, 16, 23};
	const int32_t		t3[4] = {6, 10, 15, 21};

	if (!md5)
		return (FALSE);
	ft_md5_init_set_r(md5, 0, t0);
	ft_md5_init_set_r(md5, 16, t1);
	ft_md5_init_set_r(md5, 32, t2);
	ft_md5_init_set_r(md5, 48, t3);
	ft_md5_init_set_k(md5);
	(*md5).h0 = 0x67452301;
	(*md5).h1 = 0xEFCDAB89;
	(*md5).h2 = 0x98BADCFE;
	(*md5).h3 = 0x10325476;
	return (TRUE);
}

int			ft_itohex(long int nbr, char *bytes, unsigned int size)
{
	long int		res;
	unsigned int	n;

	if (!size || !bytes)
		return (0);
	n = 0;
	while (n < size)
		bytes[n++] = (nbr >= 0) ? '0' : 'f';
	n = size - 1;
	while (nbr)
	{
		res = (nbr > 0) ? nbr % 16 : 15 + (nbr % 16);
		if (n == size - 1 && nbr < 0)
			res += 1;
		bytes[n] = (res < 10) ? res + '0' : res - 10 + 'a';
		nbr = nbr / 16;
		if (n == 0)
			break ;
		n = n - 1;
	}
	return (size);
}

static void			ft_md5_main_result(t_md5 md5, t_pchar *out)
{
	uint8_t		*(p[4]);
	t_uint		n;
	t_uint		i;

	p[0] = (uint8_t *)&md5.h0;
	p[1] = (uint8_t *)&md5.h1;
	p[2] = (uint8_t *)&md5.h2;
	p[3] = (uint8_t *)&md5.h3;
	n = 0;
	i = 0;
	while (n < 4)
	{
		ft_itohex(p[n][i], *out + (n * 8) + (i * 2), 2);
		i = i + 1;
		if (i == 4)
		{
			i = 0;
			n = n + 1;
		}
	}
	(*out)[32] = '\0';
}

#include <string.h>

extern t_bool		ft_md5_padding(t_md5 *md5, t_pchar string)
{
	t_puchar	block;
	size_t		block_size;
	size_t		string_len;
	size_t		string_len_bit;

	if (!string)
		return (FALSE);
	string_len = ft_strlen(string);
	block_size = string_len * 8 + 1;
	while (block_size % 512 != 448)
		block_size = block_size + 1;
	block_size = block_size / 8;
	if ((block = malloc(block_size + 64)) == NULL)
		return (FALSE);
	memset(block, 0, block_size + 64);
	ft_memcpy(block, string, string_len);
	block[string_len] = 128;
	string_len_bit = string_len * 8;
	ft_memcpy(block + block_size, &string_len_bit, 4);
	if (!ft_md5_loop(md5, block, block_size))
		return (FALSE);
	free(block);
	return (TRUE);
}

extern t_bool		ft_md5_main(t_pchar string, t_pchar *out)
{
	t_md5		md5;

	if (!out)
		return (FALSE);
	if (!ft_md5_init(&md5))
		return (FALSE);
	if (!ft_md5_padding(&md5, (string) ? string : ""))
		return (FALSE);
	if ((*out = malloc(32 + 1)) == NULL)
		return (FALSE);
	ft_md5_main_result(md5, out);
	return (TRUE);
}

const unsigned char			*do_md5(const unsigned char *data)
{
	char					*res;

	ft_md5_main((char*)data, &res);
	return res;
}