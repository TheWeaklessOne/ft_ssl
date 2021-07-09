#ifndef FT_SSL_MD5_FT_H
# define FT_SSL_MD5_FT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>

# include "list.h"

# define IS_E			0
# define IS_R			1
# define IS_W			2
# define IS_X			4
# define IS_D			8

# define READ_SIZE		1

typedef union	u_byte_order_32 {
	uint32_t	number;
	struct {
		uint8_t	a;
		uint8_t	b;
		uint8_t	c;
		uint8_t	d;
	}			bytes;
}				t_byte_order_32;

typedef union	u_byte_order_64 {
	uint64_t	number;
	struct {
		uint8_t	a;
		uint8_t	b;
		uint8_t	c;
		uint8_t	d;
		uint8_t	e;
		uint8_t	f;
		uint8_t	g;
		uint8_t	h;
	}			bytes;
}				t_byte_order_64;

void			*ft_malloc(size_t size);
size_t			ft_putstr_fd(const char *str, int fd);
size_t			ft_putendl_fd(const char *str, int fd);
size_t			ft_strlen(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *str);
void			ft_strextend(char **str_p, size_t size);
char			*ft_str_to_upper(const char *str);
char			**ft_strsplit(char const *s, register char c);
void			ft_free_split(register char **array);
int				ft_strncmp(register void *s1,
					register void *s2, register size_t n);
char			*ft_strchr(const char *s, int c);
void			ft_memcpy(void *to, const void *from, size_t len);
size_t			ft_strarraylen(char **array);
void			*ft_memset(void *memory, int value, size_t size);
void			ft_itoh(uint32_t number, char *output, int length);

int				ft_str_is_empty(const char *str);
void			ft_free(void **to_free);

int				ft_check_file(const char *path, unsigned check);
int				ft_open_file(const char *path);
char			*ft_read_file(int fd);

uint32_t		left_rotate_32(uint32_t a, uint32_t b);
uint32_t		right_rotate_32(uint32_t a, uint32_t b);
uint32_t		swap_endian_32(uint32_t number);
uint32_t		reverse_byte_order_32(uint32_t number);

uint64_t		left_rotate_64(uint64_t a, uint64_t b);
uint64_t		right_rotate_64(uint64_t a, uint64_t b);
uint64_t		swap_endian_64(uint64_t number);
uint64_t		reverse_byte_order_64(uint64_t number);

#endif
