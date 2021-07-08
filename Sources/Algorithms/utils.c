#include "ft.h"

/// --------------------- 32 ---------------------

uint32_t		left_rotate_32(uint32_t a, uint32_t b) {
	return (a << b) | (a >> (32 - b));
}

uint32_t		right_rotate_32(uint32_t a, uint32_t b) {
	return (a >> b) | (a << (32 - b));
}

uint32_t		swap_endian_32(uint32_t number)
{
	return (
		((number >> 24) & 0x000000FF) |
		((number >> 8) & 0x0000FF00) |
		((number << 8) & 0x00FF0000) |
		((number << 24) & 0xFF000000)
	);
}

uint32_t		reverse_byte_order_32(uint32_t number) {
	const t_byte_order_32	original = (t_byte_order_32) {
			.number = number
	};

	t_byte_order_32			reversed;

	reversed.bytes.a = original.bytes.d;
	reversed.bytes.b = original.bytes.c;
	reversed.bytes.c = original.bytes.b;
	reversed.bytes.d = original.bytes.a;

	return reversed.number;
}

/// --------------------- 64 ---------------------

uint64_t		left_rotate_64(uint64_t a, uint64_t b) {
	return (a << b) | (a >> (64 - b));
}

uint64_t		right_rotate_64(uint64_t a, uint64_t b) {
	return (a >> b) | (a << (64 - b));
}

uint64_t		swap_endian_64(const uint64_t number)
{
	return (
		(number << 56) |
		((number & 0x000000000000FF00) << 40) |
		((number & 0x0000000000FF0000) << 24) |
		((number & 0x00000000FF000000) << 8) |
		((number & 0x000000FF00000000) >> 8) |
		((number & 0x0000FF0000000000) >> 24) |
		((number & 0x00FF000000000000) >> 40) |
		(number >> 56)
	);
}

uint64_t		reverse_byte_order_64(const uint64_t number) {
	const t_byte_order_64	original = (t_byte_order_64) {
		.number = number
	};

	t_byte_order_64			reversed;

	reversed.bytes.a = original.bytes.h;
	reversed.bytes.b = original.bytes.g;
	reversed.bytes.c = original.bytes.f;
	reversed.bytes.d = original.bytes.e;
	reversed.bytes.e = original.bytes.d;
	reversed.bytes.f = original.bytes.c;
	reversed.bytes.g = original.bytes.b;
	reversed.bytes.h = original.bytes.a;

	return reversed.number;
}
