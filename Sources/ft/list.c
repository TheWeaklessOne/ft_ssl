/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <wstygg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 23:56:23 by wstygg            #+#    #+#             */
/*   Updated: 2021/01/08 23:56:23 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list			*list_add_back(t_list *list, void *content)
{
	t_list		*item;
	t_list		*ret;

	if (!list)
		return (list_create(content));
	ret = list;
	while (list->next)
		list = list->next;
	if (!(item = malloc(sizeof(t_list))))
		ft_crash("Malloc error");
	item->content = content;
	item->next = NULL;
	list->next = item;
	return (ret);
}

t_list			*list_create(void *content)
{
	t_list		*ret;

	if (!(ret = malloc(sizeof(t_list))))
		ft_crash("Malloc error");
	ret->content = content;
	ret->next = NULL;
	return (ret);
}

t_list			*list_remove_all(t_list *lst, int to_free)
{
	t_list		*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (to_free)
			free(tmp->content);
		free(tmp);
	}
	return (NULL);
}
