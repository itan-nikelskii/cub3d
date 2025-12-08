/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:28:45 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/29 15:21:42 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copy the values of n bytes from the location pointed to by src directly to
the memory block pointed to by dest. Terminating null characters in source are
not checked, so exactly n bytes are copied. To avoid overflows, the sizes of 
both dest and src must be at least n bytes. The type of the objects pointed to
by src and dest are irrelevant; the result is a binary copy of the data. 

Copying takes place as if an intermediate buffer were used, allowing dest and
src to overlap. If dest is after src, copy backward; otherwise, copy forward.
For backward copying, move both pointers to the end of the copy range; while
n is not 0, decrement both pointers and copy the values; decrement n.

The behavior is undefined if access occurs beyond the end of the dest array. */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d == s || n <= 0)
		return (dest);
	if (d > s && d < s + n)
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}

/* #include <stdio.h>
int	main(void)
{
	char str[] = "memmove can be very useful......";
	ft_memmove(str+20,str+15,11);
	puts (str);
	return (0);
} */
