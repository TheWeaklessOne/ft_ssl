/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:59:21 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/03 19:59:30 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

size_t				ft_putstr_fd(const char *str, int fd)
{
	return (write(fd, str, ft_strlen(str)));
}

size_t				ft_putendl_fd(const char *str, int fd)
{
	size_t			len;

	len = 0;
	len += write(fd, str, ft_strlen(str));
	len += write(fd, "\n", 1);
	return (len);
}

void				*ft_malloc(size_t size)
{
	register size_t	i;
	char			*ret;

	i = -1;
	if (!(ret = malloc(size)))
	{
		write(2, "Malloc error!\n", 14);
		exit(EXIT_FAILURE);
	}
	while (++i < size)
		ret[i] = 0;
	return (ret);
}

void				ft_free(void **to_free)
{
	free(*to_free);
	*to_free = NULL;
}

void				ft_crash(const char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}
