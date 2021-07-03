#include "ft_ssl.h"

#define UNKNOWN_FLAG "ft_ssl: unknown option - "
#define NO_ARG_ERR "ft_ssl: option requires an argument -- s"
#define NO_FLAG_ERR "ft_ssl: there is have to be flag-character after '-' symbol"

static char	check_symbols(const char *str, t_flags *flags, t_ssl *ssl)
{
	char	c;

	while (*str)
	{
		c = *str;
		if (c == 'p') {
			flags->p = 1;
			++ssl->p_flag_count;
		} else if (c == 'q')
			flags->q = 1;
		else if (c == 'r')
			flags->r = 1;
		else if (c == 's')
			flags->s = 1;
		else
			return (c);
		++str;
	}
	return (0);
}

static int	drop_error(const char *error, const char *str, t_ssl *ssl)
{
	ft_putendl_fd(error, 2);
	if (str)
		ft_putendl_fd(str, 2);
	ssl->error = 1;
	return (0);
}

static void	check_file_or_stdin_input(t_ssl *ssl, t_flags *flags)
{
	int		fd;
	static uint32_t is_tried_to_open_dir = 0;

	if (!*ssl->argv && !ssl->hashes && !is_tried_to_open_dir && !ssl->p_flag_count) {
		ssl->hashes = list_add_back(
				ssl->hashes,
				create_new_hash(HASH_STDIN, ft_read_file(STDIN_FILENO), NULL, NULL)
		);
	} else if (*ssl->argv) {
		while (*ssl->argv && **ssl->argv != '-') {
			is_tried_to_open_dir = 1;
			if ((fd = ft_open_file(*ssl->argv)) == -1)
				exit(EXIT_FAILURE);
			ssl->hashes = list_add_back(
					ssl->hashes,
					create_new_hash(HASH_FILE, ft_read_file(fd), *ssl->argv, flags)
			);
			++ssl->argv;
		}
	}
}

static int	flags_loop(t_ssl *ssl, t_flags *flags) {
	char	*c;
	char	*str;

	c = (char[2]){0};
	while (*ssl->argv && **ssl->argv == '-') {
		str = *ssl->argv;
		if (str[1] == '\0')
			return (drop_error(NO_FLAG_ERR, NULL, ssl));
		*c = check_symbols(str + 1, flags, ssl);
		if (flags->s) {
			if (!*(ssl->argv + 1))
				return (drop_error(NO_ARG_ERR, NULL, ssl));
			ssl->hashes = list_add_back(
					ssl->hashes,
					create_new_hash(HASH_S_FLAG, ft_strdup(*++ssl->argv), NULL, flags)
			);
			flags->s = 0;
		}
		if (*c)
			return (drop_error(UNKNOWN_FLAG, c, ssl));
		++ssl->argv;
	}
	return (1);
}

void		check_flags(t_ssl *ssl)
{
	++ssl->argv;
	t_flags	flags = {0};

	while (*ssl->argv) {
		if (!flags_loop(ssl, &flags))
			return;
		check_file_or_stdin_input(ssl, &flags);
	}
	check_file_or_stdin_input(ssl, &flags);
}
