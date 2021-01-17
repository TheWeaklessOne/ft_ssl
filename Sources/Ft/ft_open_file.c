/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:59:28 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/06 21:32:59 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				error;

	error = 0;
	if (ft_check_file(path, IS_E) <= 0)
		error += write(2, "ft_ssl: no such file - ", 23);
	else if ((ret = open(path, O_RDONLY)) < 0)
		error += write(2, "ft_ssl: can't open that file - ", 31);
	else if (!ft_check_file(path, IS_R))
		error += write(2, "ft_ssl: can't read from that file - ", 36);
	else if (ft_check_file(path, IS_D))
		error += write(2, "ft_ssl: it's a directory - ", 27);
	if (error)
	{
		ft_putendl_fd(path, 2);
		return (-1);
	}
	return (ret);
}
