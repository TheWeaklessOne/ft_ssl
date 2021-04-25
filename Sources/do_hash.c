/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:59:43 by wstygg            #+#    #+#             */
/*   Updated: 2021/04/25 17:41:43 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		do_hash(t_ssl *ssl)
{
	const unsigned char *(*apply_function)(const unsigned char *);
	t_list	*strings = ssl->flags.strings;

	if (ssl->command == MD5)
		apply_function = do_md5;
//	else if (ssl->command == SHA256)
//		apply_function = do_sha256;
	while (strings)
	{
		printf("Output: %s\n", apply_function(strings->content));
		strings = strings->next;
	}
}
