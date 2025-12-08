/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:07:47 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/29 15:03:41 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Fill the first n bytes of a contiguous block of memory (pointed to by s) 
with the unsigned char conversion of value c. 

NOTE: void * is a generic pointer type that can point to any data type, but we
cannot directly perform arithmetic (e.g., incrementing or dereferencing) on it.
This is because the size of the memory block that void * points to is unknown
since it's not associated with any particular type. To access individual bytes
of the memory region, we cast ptr to an unsigned char * (it allows the values 
to be between 0 and 255 which covers all possible byte values).

unsigned char *byte_ptr is a pointer to an unsigned char that points to where 
ptr is located, but it specifically points to bytes because of its type. */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*byte_ptr;
	size_t			i;

	byte_ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		byte_ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

/* #include <stdio.h>
int main(void) 
{
	char str[10] = "Hello";
	printf("Before memset: %s\n", str);
	ft_memset(str, '*', 4);
	printf("After memset: %s\n", str);
	return 0;
} */
