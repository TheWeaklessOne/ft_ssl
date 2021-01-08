/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:59:11 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/08 23:22:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

 int			check_command(char **argv)
{
	int				type;
	char			*upper;
	int				i;

	type = 0;
	upper = ft_str_to_upper(argv[0]);
	i = 0;
	while (++i < COMMANDS_N)
		if (!ft_strcmp(upper, get_commands()[i - 1]))
		{
			type = i;
			break ;
		}
	free(upper);
	return (type);
}

void				do_hash(t_ssl *ssl)
{
	printf("Current alg - %d\nFlags: r - %u q - %u p - %u",
		ssl->command, ssl->flags.r, ssl->flags.q, ssl->flags.p);
	t_list *lst = ssl->flags.strings;
	while (lst)
	{
		printf(" s - %s ", (char*)lst->content);
		lst = lst->next;
	}
	printf("\n");
}

 void			reset_ssl(t_ssl *ssl)
{
	ssl->flags.strings = list_remove_all(ssl->flags.strings, 1);
	ssl->flags = (t_flags){0};
}

 char			*get_command()
{
	char			*command;

	command = NULL;
	while (ft_str_is_empty(command))
		if (!(command = readline("ft_ssl> ")))
			exit(0);
	return (command);
}

 void			hashing_loop(t_ssl *ssl)
{
	char			*command;

	command = NULL;
	while (42)
	{
		free(command);
		command = get_command();
		add_history(command);
		ft_free_split(ssl->argv);
		ssl->argv = ft_strsplit(command, ' ');
		while (!(ssl->command = check_command(ssl->argv)))
		{
			put_info(command);
			ft_free((void**)&command);
			command = get_command();
			add_history(command);
			ft_free_split(ssl->argv);
			ssl->argv = ft_strsplit(command, ' ');
		}
		check_flags(ssl);
		if (!ssl->flags.error)
			do_hash(ssl);
		reset_ssl(ssl);
	}
}

 void			hash_from_args(t_ssl *ssl)
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
	t_ssl			ssl;

	ssl = (t_ssl){0};
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
