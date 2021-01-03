/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:59:11 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/03 19:59:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void			put_info(const char *command)
{
	ft_putstr_fd("ft_ssl: Error: '", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd("' is an invalid command.", 2);
	ft_putendl_fd("\nStandard commands:", 2);
	ft_putstr_fd("", 2);
	ft_putendl_fd("\nMessage Digest commands:", 2);
	ft_putendl_fd("md5\nsha256\n", 2);
	ft_putendl_fd("\nCipher commands:", 2);
	ft_putendl_fd("", 2);
}

static int			check_command(const char *command)
{
	int				type;

	type = 0;
	if (!ft_strcmp(command, "md5"))
		type = IS_MD5;
	else if (!ft_strcmp(command, "sha256"))
		type = IS_SHA256;
	return (type);
}

static void			check_flags(char ***argv_p, t_flags *flags)
{
	char			*str;

	*argv_p += 2;
	while (**argv_p && (**argv_p)[0] == '-')
	{
		str = **argv_p;
		if (!ft_strcmp(str, "-p"))
			flags->p = 1;
		else if (!ft_strcmp(str, "-q"))
			flags->q = 1;
		else if (!ft_strcmp(str, "-r"))
			flags->r = 1;
		else if (!ft_strcmp(str, "-s") && *(*argv_p + 1))
		{
			flags->s = 1;
			flags->string = ft_strdup(*(*argv_p + 1));
			++*argv_p;
		}
		else
			ft_crash(USAGE);
		++*argv_p;
	}
}

int					main(int argc, char *argv[])
{
	t_ssl			ssl;
	char			*command;

	if (argc < 2)
		ft_crash(USAGE);
	command = ft_strdup(argv[1]);
	while (!(ssl.type = check_command(command)))
	{
		put_info(argv[1]);
		free(command);
		command = readline("ft_ssl> ");
	}
	check_flags(&argv, &ssl.flags);
	while (*argv)
	{
		ft_putendl_fd(*argv, 1);
		argv++;
	}
	return (0);
}
