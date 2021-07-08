#ifndef FT_SSL_MD5_FT_SSL_H
# define FT_SSL_MD5_FT_SSL_H

# include <readline/readline.h>

# include "ft.h"

# define USAGE "usage: ft_ssl hash_type [-pqr] [-s string] [files ...]"

#define FOREACH_HASH(HASH)	\
	HASH(NONE)				\
	HASH(MD5)				\
	HASH(SHA224)			\
    HASH(SHA256)			\
    HASH(SHA512)			\
	HASH(HASH_TYPES_N)		\

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum HASH_ENUM {
	FOREACH_HASH(GENERATE_ENUM)
};

static const char *hash_type_names[HASH_TYPES_N + 1] = {
	FOREACH_HASH(GENERATE_STRING)
};

typedef enum		e_hash_kind
{
	HASH_FILE = 0,
	HASH_STDIN,
	HASH_S_FLAG
}					t_hash_kind;

typedef struct		s_flags
{
	unsigned		p : 1;
	unsigned		q : 1;
	unsigned		r : 1;
	unsigned		s : 1;
}					t_flags;

typedef struct		s_hash_info
{
	t_hash_kind		kind;
	t_flags			flags;
	const char		*hashed_value;
	const char		*unhashed_value;
	const char		*filename;
}					t_hash_info;

typedef struct		s_ssl
{
	int				hash_type;
	unsigned		error : 1;
	unsigned		p_flag_count;
	t_list			*hashes;
	char			**argv;
	char			**argv_head;
}					t_ssl;

void				do_hash(t_ssl *ssl);
int					check_command(char **argv);
void				setup_ssl(t_ssl *ssl, char *argv[]);

char				*do_md5(const char *data);
char				*do_sha224(const char *data);
char				*do_sha256(const char *data);
char				*do_sha512(const char *data);

void				free_hash(t_hash_info *info);
t_list 				*remove_all_hashes(t_list *list);
t_hash_info*		create_new_hash(t_hash_kind kind, const char* info, const char* filename, t_flags* flags);

void				check_flags(t_ssl *ssl);
void				put_info(const char *command);

void				initialize_readline(void);

#endif
