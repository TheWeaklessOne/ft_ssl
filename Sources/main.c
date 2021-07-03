#include "ft_ssl.h"

static void			reset_ssl(t_ssl *ssl)
{
	ssl->hash_type = NONE;
	ssl->hashes = remove_all_hashes(ssl->hashes);
	ft_free_split(ssl->argv_head);
	ssl->argv = NULL;
	ssl->argv_head = NULL;
	ssl->error = 0;
}

static char			*get_command(void)
{
	char			*command;

	command = NULL;
	while (ft_str_is_empty(command))
		if (!(command = readline("ft_ssl> ")) || !ft_strcmp(command, "exit"))
			exit(0);
	return (command);
}

static void			hashing_loop(t_ssl *ssl)
{
	char			*command;

	command = NULL;
	while (42)
	{
		free(command);
		command = get_command();
		add_history(command);
		ft_free_split(ssl->argv_head);
		ssl->argv_head = NULL;
		ssl->argv = ft_strsplit(command, ' ');
		ssl->argv_head = ssl->argv;
		while (!(ssl->hash_type = check_command(ssl->argv)))
		{
			put_info(command);
			ft_free((void**)&command);
			command = get_command();
			add_history(command);
			ft_free_split(ssl->argv_head);
			ssl->argv_head = NULL;
			ssl->argv = ft_strsplit(command, ' ');
			ssl->argv_head = ssl->argv;
		}
		check_flags(ssl);
		if (!ssl->error)
			do_hash(ssl);
		reset_ssl(ssl);
	}
}

static void			hash_from_args(t_ssl *ssl)
{
	if ((ssl->hash_type = check_command(ssl->argv)))
	{
		check_flags(ssl);
		if (!ssl->error)
			return (do_hash(ssl));
		ft_putendl_fd(USAGE, 2);
	}
	if (!ssl->error)
		put_info(ssl->argv[0]);
	reset_ssl(ssl);
	hashing_loop(ssl);
}

int					main(int argc, char *argv[])
{
	t_ssl			ssl = {0};

	setup_ssl(&ssl, argv);
	initialize_readline();
	if (argc > 1)
		hash_from_args(&ssl);
	else
	{
		ft_putendl_fd(USAGE, 2);
		hashing_loop(&ssl);
	}
	exit(0);
}
