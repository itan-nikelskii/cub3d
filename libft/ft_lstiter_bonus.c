/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:43:16 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/28 11:37:17 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Iterate through lst and apply the function f to the content of each node. */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/* #include <stdio.h>
void apply_increment(void *content)
{
    int *n = (int *)content;
    (*n)++;
}

int main()
{
    t_list	*node1 = (t_list *)malloc(sizeof(t_list));
    t_list	*node2 = (t_list *)malloc(sizeof(t_list));
    int		*data1 = (int *)malloc(sizeof(int));
    int		*data2 = (int *)malloc(sizeof(int));

    *data1 = 1;
    *data2 = 3;
    node1->content = data1;
    node1->next = node2;
    node2->content = data2;
    node2->next = NULL;

	printf("Original list:\n");
    t_list *temp = node1;
    while (temp)
    {
        printf("%d ", *(int *)temp->content);
        temp = temp->next;
    }
    printf("\n");

	ft_lstiter(node1, apply_increment);

	printf("Modified list (incremented by 1):\n");
    temp = node1;
    while (temp)
    {
        printf("%d ", *(int *)temp->content);
        temp = temp->next;
    }
    printf("\n");
	free(node1->content);
    free(node2->content);
    free(node1);
    free(node2);
	return (0);
} */
