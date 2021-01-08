#ifndef FT_SSL_LIST_H
# define FT_SSL_LIST_H

# include <unistd.h>
# include <stdlib.h>

typedef	struct			s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

t_list					*list_add_back(t_list *list, void *content);
t_list					*list_create(void *content);
t_list					*list_remove_all(t_list *lst, int to_free);

void					ft_crash(const char *str);

#endif
