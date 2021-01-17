/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:55:22 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/09 10:09:25 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

size_t		ft_strarraylen(char **array)
{
	size_t	ret;

	ret = 0;
	while (array[ret])
		++ret;
	return (ret);
}

int			ft_strncmp(register void *s1, register void *s2, register size_t n)
{
	register size_t			i;
	register unsigned char	litter;

	if (n == 0)
		return (0);
	i = 0;
	n--;
	while ((litter = ((unsigned char *)s1)[i]) != 0 &&
			litter == ((unsigned char *)s2)[i] && i < n)
		i++;
	return (litter - ((unsigned char *)s2)[i]);
}

char		*ft_strchr(const char *s, int c)
{
	while (s[0] != 0 && s[0] != c)
		s++;
	if (s[0] == c)
		return ((char *)s);
	return (0);
}

int			ft_str_is_empty(const char *str)
{
	char	c;

	if (!str)
		return (1);
	while (*str)
	{
		c = *str;
		if (!((c >= 9 && c <= 13) || c == ' '))
			return (0);
		++str;
	}
	return (1);
}

void		ft_memcpy(void *to, const void *from, size_t len)
{
	char			*s1;
	register size_t	i;
	const char		*s2 = from;

	i = -1;
	s1 = to;
	while (++i < len)
		s1[i] = s2[i];
}
