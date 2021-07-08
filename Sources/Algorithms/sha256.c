#include "sha256.h"

static void			chunk_loop(const uint32_t chunk[64], t_sha *sha_p) {
	uint32_t		e0;
	uint32_t		ma;
	uint32_t		t2;
	uint32_t		e1;
	uint32_t		ch;
	uint32_t		t1;

	t_sha			sha = *sha_p;

	for (register int i = 0; i < 64; ++i) {
		e0 = right_rotate_32(sha.a, 2) ^ right_rotate_32(sha.a, 13) ^ right_rotate_32(sha.a, 22);
		ma = (sha.a & sha.b) ^ (sha.a & sha.c) ^ (sha.b & sha.c);
		t2 = e0 + ma;
		e1 = right_rotate_32(sha.e, 6) ^ right_rotate_32(sha.e, 11) ^ right_rotate_32(sha.e, 25);
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

static void			extend_chunk(uint32_t chunk[64]) {
	uint32_t 		s0;
	uint32_t		s1;

	register int i;

	for (i = 0; i < 16; ++i)
		chunk[i] = swap_endian_32(chunk[i]);

	for (i = 16; i < 64; ++i) {
		s0 = right_rotate_32(chunk[i - 15], 7) ^ right_rotate_32(chunk[i - 15], 18) ^ (chunk[i - 15] >> 3);
		s1 = right_rotate_32(chunk[i - 2], 17) ^ right_rotate_32(chunk[i - 2], 19) ^ (chunk[i - 2] >> 10);
		chunk[i] = chunk[i - 16] + s0 + chunk[i - 7] + s1;
	}
}

static void			block_loop(t_sha *sha, const unsigned char *block, const size_t size_in_bytes) {
	u_int32_t		chunk[64] = {0};
	register size_t	offset;

	offset = 0;
	while (offset < size_in_bytes) {
		ft_memcpy(chunk, block + offset, 64);
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

		offset += 64;
	}
}

static void			hash(t_sha *sha, const char *data) {
	const size_t	string_len = ft_strlen(data);
	size_t			string_len_in_bits = string_len * 8;

	unsigned char	*block;
	size_t			block_size_in_bytes;

	block_size_in_bytes = string_len_in_bits + 1;
	while (block_size_in_bytes % 512 != 448)
		++block_size_in_bytes;
	block_size_in_bytes /= 8;

	block = ft_malloc(block_size_in_bytes + 8);
	ft_memcpy(block, data, string_len);
	block[string_len] = 128;
	string_len_in_bits = swap_endian_64(string_len_in_bits);
	ft_memcpy(block + block_size_in_bytes, (uint64_t*)&string_len_in_bits, 8);

	block_loop(sha, block, block_size_in_bytes + 8);
	free(block);
}

static void			calc_result(const t_sha *sha, char *result)
{
	t_digest		digest;

	digest.bytes.a = reverse_byte_order_32(sha->h0);
	digest.bytes.b = reverse_byte_order_32(sha->h1);
	digest.bytes.c = reverse_byte_order_32(sha->h2);
	digest.bytes.d = reverse_byte_order_32(sha->h3);
	digest.bytes.e = reverse_byte_order_32(sha->h4);
	digest.bytes.f = reverse_byte_order_32(sha->h5);
	digest.bytes.g = reverse_byte_order_32(sha->h6);
	digest.bytes.h = reverse_byte_order_32(sha->h7);

	for (register int i = 0; i < 32; ++i) {
		ft_itoh(digest.digest[i], result + i * 2, 2);
	}
}

char				*do_sha256(const char *data) {
	t_sha 			sha;
	char			*result;

	sha.h0 = 0x6A09E667;
	sha.h1 = 0xBB67AE85;
	sha.h2 = 0x3C6EF372;
	sha.h3 = 0xA54FF53A;
	sha.h4 = 0x510E527F;
	sha.h5 = 0x9B05688C;
	sha.h6 = 0x1F83D9AB;
	sha.h7 = 0x5BE0CD19;

	hash(&sha, data);
	result = ft_malloc(64 + 1);
	calc_result(&sha, result);
	return result;
}
