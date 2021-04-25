/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_ssl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 00:01:47 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/09 00:01:47 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void			setup_argv(t_ssl *ssl, char *argv[])
{
	register int	i;
	register int	j;

	ssl->argv = ft_malloc(sizeof(char*) * ft_strarraylen(argv));
	ssl->argv_head = ssl->argv;
	i = 0;
	j = -1;
	while (argv[++i])
		ssl->argv[++j] = ft_strdup(argv[i]);
}

void				setup_ssl(t_ssl *ssl, char *argv[])
{
	setup_argv(ssl, argv);
}
