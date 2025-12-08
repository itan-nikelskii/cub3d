/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:56:31 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/27 10:36:22 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocate memory for a new node; the ’content’ member variable is initialized 
with the given parameter ’content’. The variable ’next’ is initialized to NULL. 
Return a pointer to the new node. */
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

/* #include <stdio.h>
int main(void)
{
    char	*text = "Hello, linked list!";
    t_list	*node = ft_lstnew(text);
    if (!node)
    {
        printf("Node creation failed.\n");
        return (1);
    }
    printf("Node content: %s\n", (char *)node->content);
    free(node);
    return (0);
} */
