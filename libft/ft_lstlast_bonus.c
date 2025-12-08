/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:59:47 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/28 09:24:21 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Return the last node of the linked list. */
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

/* #include <stdio.h>
int main(void)
{
	t_list	*node1 = malloc(sizeof(t_list));
	t_list	*node2 = malloc(sizeof(t_list));
	if (!node1 || !node2)
		return (1);

	node1->content = "One";
	node1->next = node2;
	node2->content = "Two";
	node2->next = NULL;

	t_list *last = ft_lstlast(node1);
	if (last)
		printf("Last node content: %s\n", (char *)last->content);
	free(node2);
	free(node1);
	return (0);
} */
