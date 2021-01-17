/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:34:33 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/17 15:51:41 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_ssl.h"

/*
** MD5 left rotate shift constants.
*/

static uint32_t	g_md5_shift[64] = {
		7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

/*
** MD5 round constants.
*/

static uint32_t	g_md5_round[64] = {
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
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

#define A (state[0])
#define B (state[1])
#define C (state[2])
#define D (state[3])

#define A_ (state[4])
#define B_ (state[5])
#define C_ (state[6])
#define D_ (state[7])

static uint8_t	*md5_pad(const uint8_t *data, uint64_t *data_len)
{
	uint8_t		*m;
	uint64_t	len;
	uint64_t	pad_len;

	len = ft_strlen((char*)data);
	pad_len = ((len + 72) / 64) * 64;
	m = ft_malloc(pad_len);
	ft_memcpy(m, data, len);
	m[len] = 0x80;
	*data_len = pad_len;
	len *= 8;
	m[--pad_len] = len >> 56;
	m[--pad_len] = len >> 48;
	m[--pad_len] = len >> 40;
	m[--pad_len] = len >> 32;
	m[--pad_len] = len >> 24;
	m[--pad_len] = len >> 16;
	m[--pad_len] = len >> 8;
	m[--pad_len] = len;
	return (m);
}

static void		md5_rounds(uint32_t state[8],
							  uint32_t *f, uint32_t *g, uint32_t i)
{
	if (i < 16)
	{
		*f = (B & C) | ((~B) & D);
		*g = i;
	}
	else if (i < 32)
	{
		*f = (D & B) | ((~D) & C);
		*g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		*f = B ^ C ^ D;
		*g = (3 * i + 5) % 16;
	}
	else
	{
		*f = C ^ (B | (~D));
		*g = (7 * i) % 16;
	}
}

# define ROTATE_RIGHT(x, c) (((x) >> c) | ((x) << ((sizeof(x) * 8) - c)))
# define ROTATE_LEFT(x, c) (((x) << c) | ((x) >> ((sizeof(x) * 8) - c)))

static void		md5_transform(uint32_t state[8], const uint8_t *data)
{
	uint32_t	f;
	uint32_t	g;
	uint32_t	i;
	uint32_t	m[16];

	ft_memcpy(m, data, sizeof(uint32_t) * 16);
	ft_memcpy(state, state + 4, sizeof(uint32_t) * 4);
	i = 0;
	while (i < 64)
	{
		md5_rounds(state, &f, &g, i);
		f = f + A + g_md5_round[i] + m[g];
		A = D;
		D = C;
		C = B;
		B += ROTATE_LEFT(f, g_md5_shift[i]);
		++i;
	}
	A_ += A;
	B_ += B;
	C_ += C;
	D_ += D;
}

char	*bytes_to_hex(const uint8_t *bytes, size_t size)
{
	static const char	digits[16] = "0123456789abcdef";
	char				*out;
	size_t				i;
	size_t				j;

	out = ft_malloc(size * 2 + 1);
	i = 0;
	j = 0;
	while (i < size)
	{
		out[j++] = digits[(bytes[i] / 16) % 16];
		out[j++] = digits[bytes[i] % 16];
		++i;
	}
	out[j] = '\0';
	return (out);
}

char			*do_md5(const uint8_t *raw_data)
{
	uint32_t	state[8];
	uint8_t		*data;
	uint64_t	len;
	uint64_t	i;

	A_ = 0x67452301;
	B_ = 0xefcdab89;
	C_ = 0x98badcfe;
	D_ = 0x10325476;
	data = md5_pad(raw_data, &len);
	i = 0;
	while (i < len)
	{
		md5_transform(state, data + i);
		i += 64;
	}
	free(data);
	return (bytes_to_hex((uint8_t*)(state + 4), 16));
}

#undef A
#undef B
#undef C
#undef D
#undef A_
#undef B_
#undef C_
#undef D_

//#include "md5.h"
//
//static void			setup_md5(t_md5 *md5)
//{
//	md5->constants = (unsigned[64]) {
//		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
//		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
//		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
//		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
//		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
//		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
//		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
//		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
//		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
//		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
//		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
//		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
//		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
//		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
//		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
//		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
//	};
//	md5->shifts = (unsigned[64]) {
//		7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
//		5, 9, 14, 20, 5,  9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
//		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
//		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
//	};
//	md5->abcd = (unsigned[4]){0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
//	md5->aabbccdd = md5->abcd;
//}
//
//void				chunk_cycle_md5(uint8_t chunk[512])
//{
//
//}
//
//void				cycle_md5(uint8_t *new_data, size_t len, t_md5 *md5)
//{
//	register size_t	i;
//	uint8_t			chunk[512];
//
//	i = 0;
//	while (i < len)
//	{
//		ft_memcpy(chunk, new_data + i, 512);
//		i += 512;
//	}
//}
//
//char				*do_md5(const uint8_t *data)
//{
//	t_md5			md5;
//	size_t			new_len;
//	uint8_t			*new_data;
//	const size_t	len = ft_strlen((char*)data);
//
//	setup_md5(&md5);
//	new_len = len + 1;
//	while (new_len % 512 != 448)
//		++new_len;
//	new_data = ft_malloc(new_len + 64);
//	ft_memcpy(new_data, data, len);
//	*(unsigned*)(new_data + len) = 128;
//	*(unsigned*)(new_data + new_len) = (uint32_t)(8 * len);
//	return (NULL);
//}