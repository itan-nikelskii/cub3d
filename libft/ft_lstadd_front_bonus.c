/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:37:25 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/27 11:08:50 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Add the node 'new' at the beginning of the list. 'lst' is the address of a 
pointer to the first node of a list; 'new' is the address of a pointer to the 
node to be added. */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}
}

/* #include <stdio.h>
int main(void)
{
	// the right way of making a size 0 linked list to avoid pointing to garbage
    t_list	*head = NULL;
    t_list	*node1 = (t_list *)malloc(sizeof(t_list));
    t_list	*node2 = (t_list *)malloc(sizeof(t_list));
	if (!node1 || !node2)
        return (1);
    node1->content = "One";
    node1->next = NULL;
    node2->content = "Two";
    node2->next = NULL;

    ft_lstadd_front(&head, node1);
    ft_lstadd_front(&head, node2);

    t_list *tmp = head;
    while (tmp)		// print the list
    {
        printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }
	while (head)	// free the memory
    {
        t_list *tmp = head;
        head = head->next;
        free(tmp);
    }
    return (0);
} */
