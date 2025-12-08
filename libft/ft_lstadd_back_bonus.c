/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:07:43 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/28 09:25:07 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Add the node 'new' at the end of the list. 
- 'lst' is the address of a pointer to the first node of a list;
- 'new' is the address of a pointer to the node to be added. */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!*lst)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

/* #include <stdio.h>
int main(void)
{
	t_list	*node1 = malloc(sizeof(t_list));
	t_list	*node2 = malloc(sizeof(t_list));
	if (!node1 || !node2)
		return (1);

	node1->content = "One";
	node1->next = NULL;
	node2->content = "Two";
	node2->next = NULL;

	t_list	*list = node1;
	ft_lstadd_back(&list, node2);
	t_list	*current = list;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	free(node1);
	free(node2);
	return (0);
} */
