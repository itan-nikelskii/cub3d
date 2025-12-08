/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:52:54 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/29 15:45:57 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copy the values of n bytes from the location pointed to by src directly to
the memory block pointed to by dest. Terminating null characters in source are
not checked, so exactly n bytes are copied. To avoid overflows, the sizes of 
both dest and src must be at least n bytes. The type of the objects pointed to
by src and dest are irrelevant; the result is a binary copy of the data.

char *d = (char *)dest means "I want to treat the memory at dest as a sequence
of bytes regardless of the actual data type". The char type is special because 
the C standard lets us read and write any object’s representation using char *.

The behavior is undefined if:
- access occurs beyond the end of the dest array;
- the objects overlap (use memmove instead). */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	if (dest == NULL && src == NULL)
		return (dest);
	d = (char *)dest;
	s = (char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/* #include <stdio.h>
int	main(void)
{
	char str1[] = "hello bob";
	char str2[] = "byeee don";
	printf("str1 before memcpy: %s\n", str1);
	ft_memcpy(str1+6, str2+6, 3);
	printf("str1 after  memcpy: %s\n", str1);
	return (0);
} */
