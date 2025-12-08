/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 11:09:37 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/28 08:54:51 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Count and return the number of nodes in the list. */
int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

/* #include <stdio.h>
int main(void)
{
	// the right way of making a size 0 linked list to avoid pointing to garbage
    t_list	*node1 = (t_list *)malloc(sizeof(t_list));
    t_list	*node2 = (t_list *)malloc(sizeof(t_list));
	if (!node1 || !node2)
        return (1);
    node1->content = "One";
    node1->next = node2;
    node2->content = "Two";
    node2->next = NULL;

    printf("Number of nodes: %i\n", ft_lstsize(node1));

	t_list	*current = node1;
	while (current)	// free the memory
    {
        t_list	*next = current->next;
        free(current);
		current = next;
    }
    return (0);
} */
