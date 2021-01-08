#include "ft.h"

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
		if (!((c >= 9 && c <= 13 ) || c == ' '))
			return (0);
		++str;
	}
	return (1);
}