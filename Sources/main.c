/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:59:11 by wstygg            #+#    #+#             */
/*   Updated: 2021/04/25 17:46:35 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void			reset_ssl(t_ssl *ssl)
{
	ssl->command = NONE;
	ssl->flags.strings = list_remove_all(ssl->flags.strings, 1);
	ssl->flags = (t_flags){0};
	ft_free_split(ssl->argv_head);
	ssl->argv = NULL;
	ssl->argv_head = NULL;

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
		ssl->argv = ft_strsplit(command, ' ');
		ssl->argv_head = ssl->argv;
		while (!(ssl->command = check_command(ssl->argv)))
		{
			put_info(command);
			ft_free((void**)&command);
			command = get_command();
			add_history(command);
			ft_free_split(ssl->argv);
			ssl->argv = ft_strsplit(command, ' ');
			ssl->argv_head = ssl->argv;
		}
		check_flags(ssl);
		if (!ssl->flags.error)
			do_hash(ssl);
		reset_ssl(ssl);
	}
}

static void			hash_from_args(t_ssl *ssl)
{
	if ((ssl->command = check_command(ssl->argv)))
	{
		check_flags(ssl);
		if (!ssl->flags.error)
			return (do_hash(ssl));
		ft_putendl_fd(USAGE, 2);
	}
	if (!ssl->flags.error)
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
