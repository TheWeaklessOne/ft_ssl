/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 00:00:26 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/09 00:00:26 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int				check_command(char **argv)
{
	int			type;
	char		*upper;
	int			i;

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
