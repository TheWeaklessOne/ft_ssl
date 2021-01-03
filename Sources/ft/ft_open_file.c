#include "ft.h"

int				ft_check_file(const char *file, unsigned check)
{
	struct stat	st;
	int			ret;

	if (!file || stat(file, &st) == -1)
		return (-1);
	ret = 1;
	if (check & IS_D)
		ret &= S_ISDIR(st.st_mode);
	if (check & IS_R)
		ret &= ((st.st_mode & S_IRUSR) != 0);
	if (check & IS_W)
		ret &= ((st.st_mode & S_IWUSR) != 0);
	if (check & IS_X)
		ret &= ((st.st_mode & S_IXUSR) != 0);
	return (ret);
}

int				ft_open_file(const char *path)
{
	int				ret;

	if (ft_check_file(path, IS_E) <= 0)
		write(2, "No such file ", 13);
	if ((ret = open(path, O_RDONLY)) < 0)
		write(2, "Can't open that file ", 21);
	if (!ft_check_file(path, IS_R))
		write(2, "Can't read from that file ", 26);
	if (ft_check_file(path, IS_D))
		write(2, "It's a directory ", 17);
	ft_crash(path);
	return (ret);
}