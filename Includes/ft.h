
#ifndef FT_SSL_MD5_FT_H
# define FT_SSL_MD5_FT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>

# define IS_E			0
# define IS_R			1
# define IS_W			2
# define IS_X			4
# define IS_D			8

void			*ft_malloc(size_t size);
size_t			ft_putstr_fd(const char *str, int fd);
size_t			ft_putendl_fd(const char *str, int fd);
size_t			ft_strlen(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *str);
void			ft_free(void **to_free);
void			ft_crash(const char *str);

int				ft_check_file(const char *path, unsigned check);
int				ft_file_open(const char *path);

#endif
