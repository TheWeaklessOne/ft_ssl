#include "ft_ssl.h"

void			free_hash(t_hash_info *info) {
	free((void*)info->hashed_value);
	free((void*)info->unhashed_value);
	free(info);
}

t_list 			*remove_all_hashes(t_list *list) {
	t_hash_info	*info;
	void		*to_free;

	while (list) {
		info = list->content;
		free_hash(info);
		to_free = list;
		list = list->next;
		free(to_free);
	}
	return NULL;
}

t_hash_info*	create_new_hash(const t_hash_kind kind, const char* info, const char* filename, t_flags* flags) {
	t_hash_info *ret = ft_malloc(sizeof(t_hash_info));
	ret->kind = kind;
	ret->unhashed_value = info;
	ret->filename = filename;
	if (flags) {
		ret->flags = *flags;
		flags->p = 0;
	}
	return ret;
}
