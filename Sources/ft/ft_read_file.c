#include "ft.h"

char				*ft_read_file(int fd)
{
	register size_t	i;
	char			*file;
	size_t			bytes;

	i = 0;
	if (!(file = malloc(READ_SIZE + 1)))
		ft_crash("Malloc error!");
	file[READ_SIZE] = 0;
	while ((bytes = read(fd, file + (i++ * READ_SIZE), READ_SIZE)) == READ_SIZE)
		ft_strextend(&file, READ_SIZE);
	file[(i - 1) * READ_SIZE + bytes] = 0;
	return (file);
}