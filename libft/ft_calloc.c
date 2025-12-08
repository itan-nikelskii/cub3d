/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:50:07 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/30 14:41:11 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

/* Allocate a block of memory for an array of nmemb elements, each of them size
bytes long, and initializes all its bits to zero. If size or nmemb are zero,
return a pointer that can be passed to free(). If (nmemb * size) results in 
overflow, return NULL. */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (SIZE_MAX / nmemb < size)
		return (NULL);
	result = malloc(nmemb * size);
	if (!result)
		return (NULL);
	ft_bzero(result, nmemb * size);
	return (result);
}

/* #include <stdio.h>
int	main(void)
{
	int		*arr;
	size_t	n = 5;

	arr = (int *)ft_calloc(n, sizeof(int));
	if (!arr)
	{
		printf("Memory allocation failed.\n");
		return (1);
	}
	printf("ft_calloc allocated memory for %ld integers. Values:\n", n);
	for (size_t i = 0; i < n; i++)
	{
		printf("arr[%ld] = %d\n", i, arr[i]);
	}
	free(arr);
	return (0);
} */
