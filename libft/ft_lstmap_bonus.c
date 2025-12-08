/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:18:07 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/30 14:42:51 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Create a new node with transformed content by applying the function f to the
content of the original node. Note that "content = f(lst_node->content)" can
sometimes mean that content is NULL because this is exactly what f does, so
no NULL check for content is present here. */
static t_list	*ft_create_mapped_node(
	t_list *lst_node, void *(*f)(void *), void (*del)(void *))
{
	void	*content;
	t_list	*new_node;

	content = f(lst_node->content);
	new_node = ft_lstnew(content);
	if (!new_node)
	{
		del(content);
		return (NULL);
	}
	return (new_node);
}

/* Iterate through the list, apply the function 'f' to each node’s content, and
build  a new list resulting of the successive applications of the function 'f'.
The 'del' function is used to delete the content of a node if needed. */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_node = ft_create_mapped_node(lst, f, del);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}
