/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:59:24 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/06 22:14:55 by wstygg           ###   ########.fr       */
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

	if (!str)
		return (NULL);
	out = malloc(ft_strlen(str) + 1);
	if (!out)
		ft_crash("Malloc error!");
	count = 0;
	while ((c = str[count]))
	{
		out[count] = c;
		count++;
	}
	out[count] = 0;
	return (out);
}

void				ft_strextend(char **str_p, size_t size)
{
	register size_t	i;
	char			*new_str;
	const char		*str = *str_p;
	const size_t	len = ft_strlen(str);
	const size_t	new_len = len + size + 1;

	if (!(new_str = malloc(new_len)))
		ft_crash("Malloc error!");
	i = -1;
	while (++i < len)
		new_str[i] = str[i];
	--i;
	while (++i < new_len)
		new_str[i] = 0;
	free(*str_p);
	*str_p = new_str;
}

char				*ft_str_to_upper(const char *str)
{
	char			c;
	register size_t	i;
	char			*ret;
	const size_t	len = ft_strlen(str);

	i = -1;
	if (!(ret = malloc(len + 1)))
		ft_crash("Malloc error!");
	while (++i < len)
	{
		c = str[i];
		if (c >= 'a' && c <= 'z')
			c -= 32;
		ret[i] = c;
	}
	return (ret);
}