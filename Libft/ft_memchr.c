/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:49:32 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/29 14:48:59 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Scan the initial n bytes of the memory area pointed to by s for the first
instance of c. Both c and the bytes of the memory area pointed to by s are
interpreted as unsigned char. Return a pointer to the matching byte or NULL if
the character does not occur in the given memory area. */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)s;
	while (n > 0)
	{
		if (*byte_ptr == (unsigned char)c)
			return ((void *)byte_ptr);
		byte_ptr++;
		n--;
	}
	return (NULL);
}

/* #include <stdio.h>
int	main(void)
{
	const char	str[] = "Hello, world!";
	int			c = 'o';
	size_t		n = 13;

	char *result = ft_memchr(str, c, n);
	if (result != NULL)		
 		printf("Character '%c' found at position: %ld\n", c, result - str);
	else
		printf("Character '%c' not found in the first %ld bytes.\n", c, n);

	return (0);
} */
