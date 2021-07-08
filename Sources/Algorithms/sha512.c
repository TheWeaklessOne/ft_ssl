#include "sha512.h"

static void			chunk_loop(const u_int64_t chunk[80], t_sha *sha_p) {
	uint64_t		e0;
	uint64_t		ma;
	uint64_t		t2;
	uint64_t		e1;
	uint64_t		ch;
	uint64_t		t1;

	t_sha			sha = *sha_p;

	for (register int i = 0; i < 64; ++i) {
		e0 = right_rotate_64(sha.a, 28) ^ right_rotate_64(sha.a, 34) ^ right_rotate_64(sha.a, 39);
		ma = (sha.a & sha.b) ^ (sha.a & sha.c) ^ (sha.b & sha.c);
		t2 = e0 + ma;
		e1 = right_rotate_64(sha.e, 14) ^ right_rotate_64(sha.e, 18) ^ right_rotate_64(sha.e, 41);
		ch = (sha.e & sha.f) ^ ((~sha.e) & sha.g);
		t1 = sha.h + e1 + ch + constants[i] + chunk[i];

		sha.h = sha.g;
		sha.g = sha.f;
		sha.f = sha.e;
		sha.e = sha.d + t1;
		sha.d = sha.c;
		sha.c = sha.b;
		sha.b = sha.a;
		sha.a = t1 + t2;
	}
	*sha_p = sha;
}

static void			extend_chunk(u_int64_t chunk[80]) {
	uint64_t 		s0;
	uint64_t		s1;

	register int i;

	for (i = 0; i < 16; ++i)
		chunk[i] = swap_endian_64(chunk[i]);

	for (i = 16; i < 80; ++i) {
		s0 = right_rotate_64(chunk[i - 15], 1) ^ right_rotate_64(chunk[i - 15], 8) ^ (chunk[i - 15] >> 7);
		s1 = right_rotate_64(chunk[i - 2], 19) ^ right_rotate_64(chunk[i - 2], 61) ^ (chunk[i - 2] >> 6);
		chunk[i] = chunk[i - 16] + s0 + chunk[i - 7] + s1;
	}
}

static void			block_loop(t_sha *sha, const unsigned char *block, const size_t size_in_bytes) {
	u_int64_t		chunk[80] = {0};
	register size_t	offset;

	offset = 0;
	while (offset < size_in_bytes) {
		ft_memcpy(chunk, block + offset, 128);
		extend_chunk(chunk);

		sha->a = sha->h0;
		sha->b = sha->h1;
		sha->c = sha->h2;
		sha->d = sha->h3;
		sha->e = sha->h4;
		sha->f = sha->h5;
		sha->g = sha->h6;
		sha->h = sha->h7;

		chunk_loop(chunk, sha);

		sha->h0 += sha->a;
		sha->h1 += sha->b;
		sha->h2 += sha->c;
		sha->h3 += sha->d;
		sha->h4 += sha->e;
		sha->h5 += sha->f;
		sha->h6 += sha->g;
		sha->h7 += sha->h;

		offset += 128;
	}
}

static void			hash(t_sha *sha, const char *data) {
	const size_t	string_len = ft_strlen(data);
	size_t			string_len_in_bits = string_len * 8;

	unsigned char	*block;
	size_t			block_size_in_bytes;

	block_size_in_bytes = string_len_in_bits + 1;
	while (block_size_in_bytes % 1024 != 896)
		++block_size_in_bytes;
	block_size_in_bytes /= 8;

	block = ft_malloc(block_size_in_bytes + 16);
	ft_memcpy(block, data, string_len);
	block[string_len] = 128;
	string_len_in_bits = swap_endian_64(string_len_in_bits);
	ft_memcpy(block + block_size_in_bytes, &string_len_in_bits, 16);

	block_loop(sha, block, block_size_in_bytes + 16);
	free(block);
}

static void			calc_result(const t_sha *sha, char *result)
{
	t_digest		digest;

	digest.bytes.a = reverse_byte_order_64(sha->h0);
	digest.bytes.b = reverse_byte_order_64(sha->h1);
	digest.bytes.c = reverse_byte_order_64(sha->h2);
	digest.bytes.d = reverse_byte_order_64(sha->h3);
	digest.bytes.e = reverse_byte_order_64(sha->h4);
	digest.bytes.f = reverse_byte_order_64(sha->h5);
	digest.bytes.g = reverse_byte_order_64(sha->h6);
	digest.bytes.h = reverse_byte_order_64(sha->h7);

	for (register int i = 0; i < 64; ++i) {
		ft_itoh(digest.digest[i], result + i * 2, 2);
	}
}

char				*do_sha512(const char *data) {
	t_sha 			sha;
	char			*result;

	sha.h0 = 0x6a09e667f3bcc908;
	sha.h1 = 0xbb67ae8584caa73b;
	sha.h2 = 0x3c6ef372fe94f82b;
	sha.h3 = 0xa54ff53a5f1d36f1;
	sha.h4 = 0x510e527fade682d1;
	sha.h5 = 0x9b05688c2b3e6c1f;
	sha.h6 = 0x1f83d9abfb41bd6b;
	sha.h7 = 0x5be0cd19137e2179;

	hash(&sha, data);
	result = ft_malloc(128 + 1);
	calc_result(&sha, result);
	return result;
}
