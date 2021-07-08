#include "md5.h"

static void			chunk_loop(const uint32_t chunk[16], t_md5 *md5) {
	uint32_t		F;
	uint32_t		g;

	for (register int i = 0; i < 64; ++i) {
		if (i < 16) {
			F = (md5->B & md5->C) | (~md5->B & md5->D);
			g = i;
		} else if (i < 32) {
			F = (md5->D & md5->B) | (~md5->D & md5->C);
			g = (5 * i + 1) % 16;
		} else if (i < 48) {
			F = md5->B ^ md5->C ^ md5->D;
			g = (3 * i + 5) % 16;
		} else {
			F = md5->C ^ (md5->B | ~md5->D);
			g = (7 * i) % 16;
		}

		F += md5->A + constants[i] + chunk[g];
		md5->A = md5->D;
		md5->D = md5->C;
		md5->C = md5->B;
		md5->B += left_rotate_32(F, shifts[i]);
	}
}

static void			block_loop(t_md5 *md5, const unsigned char *block, const size_t size_in_bytes) {
	u_int32_t		chunk[16] = {0};
	register size_t	offset;

	offset = 0;
	while (offset < size_in_bytes) {
		ft_memcpy(chunk, block + offset, 64);

		md5->A = md5->a0;
		md5->B = md5->b0;
		md5->C = md5->c0;
		md5->D = md5->d0;

		chunk_loop(chunk, md5);

		md5->a0 += md5->A;
		md5->b0 += md5->B;
		md5->c0 += md5->C;
		md5->d0 += md5->D;

		offset += 64;
	}
}

static void			hash(t_md5 *md5, const char *data) {
	const size_t	string_len = ft_strlen(data);
	const size_t	string_len_in_bits = string_len * 8;

	unsigned char	*block;
	size_t			block_size_in_bytes;

	block_size_in_bytes = string_len_in_bits + 1;
	while (block_size_in_bytes % 512 != 448)
		++block_size_in_bytes;
	block_size_in_bytes /= 8;

	block = ft_malloc(block_size_in_bytes + sizeof(uint64_t));
	ft_memcpy(block, data, string_len);
	block[string_len] = 128;
	ft_memcpy(block + block_size_in_bytes, (uint64_t*)&string_len_in_bits, 8);

	block_loop(md5, block, block_size_in_bytes + 8);
	free(block);
}

static void			calc_result(const t_md5* md5, char *result)
{
	t_digest		digest;

	digest.bytes.a = md5->a0;
	digest.bytes.b = md5->b0;
	digest.bytes.c = md5->c0;
	digest.bytes.d = md5->d0;

	for (register int i = 0; i < 16; ++i)
		ft_itoh(digest.digest[i], result + i * 2, 2);
}

char				*do_md5(const char *data) {
	t_md5			md5;
	char			*result;

	md5.a0 = 0x67452301;
	md5.b0 = 0xEFCDAB89;
	md5.c0 = 0x98BADCFE;
	md5.d0 = 0x10325476;
	hash(&md5, data);
	result = ft_malloc(32 + 1);
	calc_result(&md5, result);
	return result;
}
