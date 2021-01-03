/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:59:24 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/03 20:00:55 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

size_t				ft_strlen(const char *str)
{
	register size_t	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int					ft_strcmp(const register char *s1, register const char *s2)
{
	register size_t	i;
	register char	litter;

	i = 0;
	while ((litter = s1[i]) != 0 && litter == s2[i])
		i++;
	return ((unsigned char)litter - (unsigned char)s2[i]);
}

char				*ft_strdup(const char *str)
{
	register size_t	count;
	register char	*out;
	register char	c;

	out = (char*)ft_malloc(ft_strlen(str) + 1);
	count = 0;
	while ((c = str[count]))
	{
		out[count] = c;
		count++;
	}
	out[count] = 0;
	return (out);
}
