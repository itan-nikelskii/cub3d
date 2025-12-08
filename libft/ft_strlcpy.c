/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inikelsk <inikelsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:37:40 by inikelsk          #+#    #+#             */
/*   Updated: 2025/04/23 11:22:54 by inikelsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copy up to (size - 1) bytes from the NUL-terminated string src to dest; the
result is guaranteed to be NUL-terminated as long as size > 0. Return the total
length of the string that was attempted to be created (= length of src). 

Undefined behavior if dest is not large enough (programmer's responsibility).

Note that "if (size > 0)" is a guard against potential underflow in the while
loop that follows (since size_t is an unsigned type and cannot be negative). */
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_length;
	size_t	i;

	src_length = 0;
	while (src[src_length])
	{
		src_length++;
	}
	if (size > 0)
	{
		i = 0;
		while (i < (size - 1) && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (src_length);
}

/* #include <stdio.h>
int	main(void)
{
	char	*source = "hello";
	char	destination[2];

	size_t result = ft_strlcpy(destination, source, 4);
	printf("%s\n", destination);
	printf("%ld\n", result);
	return (0);
} */
