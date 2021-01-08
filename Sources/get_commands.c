/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:02:34 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/06 22:43:26 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

const char		**get_commands(void)
{
	static const char	*commands[3] = {
			"MD5",
			"SHA256",
			NULL
	};

	return (commands);
}
