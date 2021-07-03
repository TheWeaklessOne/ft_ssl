#include "ft.h"

uint32_t		left_rotate(const uint32_t a, const uint32_t b) {
	return (((a) << (b)) | ((a) >> (32 - (b))));
}

uint32_t		right_rotate(const uint32_t a, const uint32_t b) {
	return (((a) >> (b)) | ((a) << (32 - (b))));
}

uint32_t		swap_endian_32(uint32_t n)
{
	return (
			((n >> 24) & 0x000000ff) |
			((n >> 8) & 0x0000ff00) |
			((n << 8) & 0x00ff0000) |
			((n << 24) & 0xff000000)
	);
}

uint64_t		swap_endian_64(uint64_t n)
{
	return (
			((n << 56) |
			 ((n & 0x000000000000FF00) << 40) |
			 ((n & 0x0000000000FF0000) << 24) |
			 ((n & 0x00000000FF000000) << 8) |
			 ((n & 0x000000FF00000000) >> 8) |
			 ((n & 0x0000FF0000000000) >> 24) |
			 ((n & 0x00FF000000000000) >> 40) |
			 (n >> 56))
	);
}