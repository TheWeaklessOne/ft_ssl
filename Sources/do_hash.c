/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:59:43 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/09 00:00:58 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		do_hash(t_ssl *ssl)
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
