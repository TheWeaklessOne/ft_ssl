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

void		*ft_memset(void *memory, int value, size_t size)
{
	register size_t	i = 0;
	char			*temp = memory;

	while (i < size)
	{
		temp[i] = value;
		++i;
	}
	return (memory);
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

void			ft_itoh(uint32_t number, char *output, int length) {
	char c;

	for (register int i = length - 1; i != -1; --i) {
		c = (char)(number % 16);
		if (c < 10)
			output[i] = (char)(c + '0');
		else
			output[i] = (char)(c - 10 + 'a');
		number /= 16;
	}
}
