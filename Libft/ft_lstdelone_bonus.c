/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:26:25 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/28 10:17:56 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Free the content of the node 'lst' using the function 'del'. Free just the
node itself, NOT the next node.  */
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}

/* 
// put this on top for testing
void	del(void *content) 
{
    free(content);
}
#include <stdio.h>
int main() 
{
    t_list	*node1 = (t_list *)malloc(sizeof(t_list));
    t_list	*node2 = (t_list *)malloc(sizeof(t_list));
    int		*data1 = (int *)malloc(sizeof(int));
    int		*data2 = (int *)malloc(sizeof(int));

    *data1 = 1;
    *data2 = 42;

    node1->content = data1;
    node1->next = node2;
    node2->content = data2;
    node2->next = NULL;

    printf("Before deletion of node1:\n");
    printf("Node 1 content: %d\n", *(int *)node1->content);
    printf("Node 2 content: %d\n", *(int *)node2->content);

	ft_lstdelone(node1, del);				// delete the first node

    printf("\nAfter deletion of node1:\n");	// check if node2 is still good
    printf("Node 2 content: %d\n", *(int *)node2->content);

    ft_lstdelone(node2, del);
    return (0);
} */
