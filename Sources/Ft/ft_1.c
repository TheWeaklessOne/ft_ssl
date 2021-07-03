#include "ft.h"

size_t				ft_putstr_fd(const char *str, int fd)
{
	if (!str)
		return 0;
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
	ret = malloc(size);
	if (!ret)
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
