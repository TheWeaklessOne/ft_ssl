#include "ft_ssl.h"

static void	print_name(const t_hash_info *info) {
	if (info->kind == HASH_S_FLAG) {
		ft_putstr_fd("\"", 1);
		ft_putstr_fd(info->unhashed_value, 1);
		ft_putstr_fd("\"", 1);
	} else {
		ft_putstr_fd(info->filename, 1);
	}
}

static void	print_hash(const t_hash_info *info, t_ssl *ssl) {
	const char* 	hash_type = hash_type_names[ssl->hash_type];

	if (info->kind == HASH_STDIN || info->flags.q == 1u) {
		ft_putstr_fd(info->hashed_value, 1);
	} else {
		if (!info->flags.r) {
			ft_putstr_fd(hash_type, 1);
			ft_putstr_fd("(", 1);

			print_name(info);

			ft_putstr_fd(")", 1);
			ft_putstr_fd(" = ", 1);
		}
		ft_putstr_fd(info->hashed_value, 1);
		if (info->flags.r) {
			ft_putstr_fd(" ", 1);
			print_name(info);
		}
	}
	ft_putstr_fd("\n", 1);
}

static int p_flag_is_used = 0;

static void	do_p_flag(t_ssl *ssl, char *(apply_function)(const char*)) {

	t_hash_info *info = NULL;

	--ssl->p_flag_count;
	if (p_flag_is_used) {
		info = create_new_hash(HASH_STDIN, ft_strdup(""), NULL, NULL);
		info->hashed_value = apply_function(info->unhashed_value);
	} else {
		p_flag_is_used = 1;
		info = create_new_hash(HASH_STDIN, ft_read_file(STDIN_FILENO), NULL, NULL);
		info->hashed_value = apply_function(info->unhashed_value);
	}
	const char *text = info->unhashed_value;
	if (ft_strlen(text)) {
		if (text[ft_strlen(text) - 1] == '\n')
			ft_putstr_fd(text, 1);
		else
			ft_putendl_fd(text, 1);
	}
	print_hash(info, ssl);
	free_hash(info);
}

static char *(*apply_functions[HASH_TYPES_N])(const char*) = {
		NULL,
		do_md5,
		do_sha256
};

void		do_hash(t_ssl *ssl) {
	char *(*apply_function)(const char *);
	t_list		*hashes = ssl->hashes;
	t_hash_info *info;

	apply_function = apply_functions[ssl->hash_type];
	while (hashes)
	{
		info = hashes->content;
		info->hashed_value = apply_function(info->unhashed_value);
		if (info->flags.p)
			do_p_flag(ssl, apply_function);
		print_hash(info, ssl);
		hashes = hashes->next;
	}
	while (ssl->p_flag_count)
		do_p_flag(ssl, apply_function);
	p_flag_is_used = 0;
}
