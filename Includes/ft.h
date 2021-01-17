/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 19:59:15 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/09 10:09:25 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_FT_H
# define FT_SSL_MD5_FT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>

# include "list.h"

# define IS_E			0
# define IS_R			1
# define IS_W			2
# define IS_X			4
# define IS_D			8

# define READ_SIZE		3

void			*ft_malloc(size_t size);
size_t			ft_putstr_fd(const char *str, int fd);
size_t			ft_putendl_fd(const char *str, int fd);
size_t			ft_strlen(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *str);
void			ft_strextend(char **str_p, size_t size);
char			*ft_str_to_upper(const char *str);
char			**ft_strsplit(char const *s, register char c);
void			ft_free_split(register char **array);
int				ft_strncmp(register void *s1,
					register void *s2, register size_t n);
char			*ft_strchr(const char *s, int c);
void			ft_memcpy(void *to, const void *from, size_t len);
size_t			ft_strarraylen(char **array);

int				ft_str_is_empty(const char *str);
void			ft_free(void **to_free);

int				ft_check_file(const char *path, unsigned check);
int				ft_open_file(const char *path);
char			*ft_read_file(int fd);

#endif
